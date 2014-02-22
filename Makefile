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

LIBS = -lz

ifeq ($(platform), unix)
   fpic := -fPIC
   TARGET := $(TARGET_NAME)_libretro.so
   SHARED := -shared -Wl,-version-script=$(LIBRETRO_DIR)/link.T -Wl,-no-undefined
else ifeq ($(platform),osx)
   fpic := -fPIC
   TARGET := $(TARGET_NAME)_libretro.dylib
	SHARED := -dynamiclib
else ifeq ($(platform),ios)
   fpic := -fPIC
   TARGET := $(TARGET_NAME)_libretro_ios.dylib
   SHARED := -dynamiclib -miphoneos-version-min=5.0
   CC = clang -arch armv7 -isysroot $(IOSSDK) -miphoneos-version-min=5.0
   CXX = clang++ -arch armv7 -isysroot $(IOSSDK) -miphoneos-version-min=5.0
else ifeq ($(platform),qnx)
   fpic := -fPIC
   TARGET := $(TARGET_NAME)_libretro_qnx.so
   SHARED := -shared -Wl,-version-script=$(LIBRETRO_DIR)/link.T -Wl,-no-undefined
	CC = qcc -Vgcc_ntoarmv7le
	CXX = QCC -Vgcc_ntoarmv7le_cpp
else ifeq ($(platform),psp1)
   TARGET := $(TARGET_NAME)_libretro_psp1.a
	CC = psp-gcc
	CXX = psp-g++
	AR = psp-ar
	FLAGS += -G0 -DLSB_FIRST -DWANT_CRC32
	STATIC_LINKING := 1
	LIBS :=
else
   fpic :=
   TARGET := $(TARGET_NAME)_libretro.dll
   CC = gcc
   CXX = g++
   SHARED := -shared -static-libgcc -static-libstdc++ -Wl,-no-undefined -Wl,-version-script=$(LIBRETRO_DIR)/link.T
endif

CXXSRCS := lynx/lynxdec.cpp lynx/Cart.cpp lynx/Memmap.cpp lynx/Mikie.cpp lynx/Ram.cpp lynx/Rom.cpp lynx/Susie.cpp lynx/System.cpp libretro/libretro.cpp

CXXOBJ := $(CXXSRCS:.cpp=.o)

OBJS := $(CXXOBJ)


INCDIRS = -Ilynx/ -Ilibretro/

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

$(TARGET): $(OBJS)
ifeq ($(STATIC_LINKING), 1)
	$(AR) rcs $@ $(OBJS)
else
	$(CXX) -o $@ $(SHARED) $(OBJS) $(LDFLAGS) $(LIBS)
endif

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCDIRS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCDIRS)

clean-objs:
	rm -f $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

.PHONY: clean clean-objs all
