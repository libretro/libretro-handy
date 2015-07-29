TARGET_NAME := handy

ifeq ($(platform),)
	platform = unix
	ifeq ($(shell uname -a),)
		platform = win
	else ifneq ($(findstring MINGW,$(shell uname -a)),)
		platform = win
	else ifneq ($(findstring Darwin,$(shell uname -a)),)
		platform = osx
	else ifneq ($(findstring win,$(shell uname -a)),)
		platform = win
	endif
endif

LIBRETRO_DIR := libretro
CORE_DIR := src

# system platform
system_platform = unix
ifeq ($(shell uname -a),)
	EXE_EXT = .exe
	system_platform = win
else ifneq ($(findstring Darwin,$(shell uname -a)),)
	system_platform = osx
else ifneq ($(findstring MINGW,$(shell uname -a)),)
	system_platform = win
endif

# Unix
ifeq ($(platform), unix)
	fpic := -fPIC
	TARGET := $(TARGET_NAME)_libretro.so
	SHARED := -shared -Wl,-version-script=$(LIBRETRO_DIR)/link.T -Wl,-no-undefined
	FLAGS += -DWANT_CRC32

# OS X
else ifeq ($(platform),osx)
	fpic := -fPIC
	TARGET := $(TARGET_NAME)_libretro.dylib
	SHARED := -dynamiclib
	FLAGS += -DWANT_CRC32
	LIBS :=
	OSXVER = `sw_vers -productVersion | cut -d. -f 2`
	OSX_LT_MAVERICKS = `(( $(OSXVER) <= 9)) && echo "YES"`
	ifeq ($(OSX_LT_MAVERICKS),"YES")
		fpic += -mmacosx-version-min=10.5
	endif
	ifndef ($(NOUNIVERSAL))
		CFLAGS  += $(ARCHFLAGS)
		CXXFLAGS  += $(ARCHFLAGS)
		LDFLAGS += $(ARCHFLAGS)
	endif

# iOS
else ifeq ($(platform),ios)
	fpic := -fPIC
	TARGET := $(TARGET_NAME)_libretro_ios.dylib
	SHARED := -dynamiclib
	ifeq ($(IOSSDK),)
		IOSSDK := $(shell xcodebuild -version -sdk iphoneos Path)
	endif
	CC = clang -arch armv7 -isysroot $(IOSSDK)
	CXX = clang++ -arch armv7 -isysroot $(IOSSDK)
	FLAGS += -DWANT_CRC32
	LIBS :=
	OSXVER = `sw_vers -productVersion | cut -d. -f 2`
	OSX_LT_MAVERICKS = `(( $(OSXVER) <= 9)) && echo "YES"`
	ifeq ($(OSX_LT_MAVERICKS),"YES")
		SHARED += -miphoneos-version-min=5.0
		CC +=  -miphoneos-version-min=5.0
		CXX +=  -miphoneos-version-min=5.0
	endif

# Theos iOS
else ifeq ($(platform), theos_ios)
	DEPLOYMENT_IOSVERSION = 5.0
	TARGET = iphone:latest:$(DEPLOYMENT_IOSVERSION)
	ARCHS = armv7 armv7s
	TARGET_IPHONEOS_DEPLOYMENT_VERSION=$(DEPLOYMENT_IOSVERSION)
	THEOS_BUILD_DIR := objs
	include $(THEOS)/makefiles/common.mk
	LIBRARY_NAME = $(TARGET_NAME)_libretro_ios
	FLAGS += -DWANT_CRC32

# QNX
else ifeq ($(platform),qnx)
	fpic := -fPIC
	TARGET := $(TARGET_NAME)_libretro_qnx.so
	SHARED := -shared -Wl,-version-script=$(LIBRETRO_DIR)/link.T -Wl,-no-undefined
	CC = qcc -Vgcc_ntoarmv7le
	CXX = QCC -Vgcc_ntoarmv7le_cpp
	FLAGS += -DWANT_CRC32

# PS3
else ifeq ($(platform),ps3)
	TARGET := $(TARGET_NAME)_libretro_ps3.a
	CC = $(CELL_SDK)/host-win32/ppu/bin/ppu-lv2-gcc.exe
	CXX = $(CELL_SDK)/host-win32/ppu/bin/ppu-lv2-g++.exe
	AR = $(CELL_SDK)/host-win32/ppu/bin/ppu-lv2-ar.exe
	FLAGS += -DMSB_FIRST -DWANT_CRC32
	STATIC_LINKING := 1
	LIBS :=

# sncps3
else ifeq ($(platform), sncps3)
	TARGET := $(TARGET_NAME)_libretro_ps3.a
	CC = $(CELL_SDK)/host-win32/sn/bin/ps3ppusnc.exe
	CXX = $(CELL_SDK)/host-win32/sn/bin/ps3ppusnc.exe
	AR = $(CELL_SDK)/host-win32/sn/bin/ps3snarl.exe
	FLAGS += -DMSB_FIRST -DWANT_CRC32
	STATIC_LINKING := 1
	LIBS :=

# PSP
else ifeq ($(platform),psp1)
	TARGET := $(TARGET_NAME)_libretro_psp1.a
	CC = psp-gcc$(EXE_EXT)
	CXX = psp-g++$(EXE_EXT)
	AR = psp-ar$(EXE_EXT)
	FLAGS += -G0 -DLSB_FIRST -DWANT_CRC32
	STATIC_LINKING := 1
	LIBS :=

# ARM
else ifneq (,$(findstring armv,$(platform)))
	TARGET := $(TARGET_NAME)_libretro.so
	SHARED := -shared -Wl,-version-script=$(LIBRETRO_DIR)/link.T -Wl,-no-undefined
	FLAGS += -DWANT_CRC32
	fpic := -fPIC
	ifneq (,$(findstring cortexa5,$(platform)))
		FLAGS += -marm -mcpu=cortex-a5
	else ifneq (,$(findstring cortexa8,$(platform)))
		FLAGS += -marm -mcpu=cortex-a8
	else ifneq (,$(findstring cortexa9,$(platform)))
		FLAGS += -marm -mcpu=cortex-a9
	else ifneq (,$(findstring cortexa15a7,$(platform)))
		FLAGS += -marm -mcpu=cortex-a15.cortex-a7
	else
		FLAGS += -marm
	endif
	ifneq (,$(findstring softfloat,$(platform)))
		FLAGS += -mfloat-abi=softfp
	else ifneq (,$(findstring hardfloat,$(platform)))
		FLAGS += -mfloat-abi=hard
	endif

# Windows
else
	fpic :=
	TARGET := $(TARGET_NAME)_libretro.dll
	CC = gcc
	CXX = g++
	SHARED := -shared -static-libgcc -static-libstdc++ -Wl,-no-undefined -Wl,-version-script=$(LIBRETRO_DIR)/link.T
	FLAGS += -DWANT_CRC32

endif

CORE_DIR := .

include Makefile.common

OBJECTS := $(SOURCES_CXX:.cpp=.o)

ifeq ($(DEBUG),1)
FLAGS += -O0
else ifeq ($(platform),psp1)
FLAGS += -O2
else
FLAGS += -O3 
endif

FLAGS += -fomit-frame-pointer -fno-tree-vectorize -I. $(fpic) $(libs) $(includes)
CXXFLAGS += $(FLAGS)
CFLAGS += $(FLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCFLAGS)

ifeq ($(platform), theos_ios)
COMMON_FLAGS := -DIOS $(COMMON_DEFINES) $(INCFLAGS) -I$(THEOS_INCLUDE_PATH) -Wno-error
$(LIBRARY_NAME)_CFLAGS += $(CFLAGS) $(COMMON_FLAGS)
$(LIBRARY_NAME)_CXXFLAGS += $(CXXFLAGS) $(COMMON_FLAGS)
${LIBRARY_NAME}_FILES = $(SOURCES_CXX) $(SOURCES_C)
include $(THEOS_MAKE_PATH)/library.mk
else
all: $(TARGET)
$(TARGET): $(OBJECTS)
ifeq ($(STATIC_LINKING), 1)
	$(AR) rcs $@ $(OBJECTS)
else
	$(CXX) -o $@ $(SHARED) $(OBJECTS) $(LDFLAGS) $(LIBS)
endif

clean-objs:
	rm -f $(OBJECTS)

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

.PHONY: clean clean-objs all
endif
