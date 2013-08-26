LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(TARGET_ARCH),arm)
LOCAL_CFLAGS += -DANDROID_ARM
LOCAL_ARM_MODE := arm
endif

ifeq ($(TARGET_ARCH),x86)
LOCAL_CFLAGS +=  -DANDROID_X86
endif

ifeq ($(TARGET_ARCH),mips)
LOCAL_CFLAGS += -DANDROID_MIPS
endif

LOCAL_MODULE    := libretro
LOCAL_LDLIBS    += -lz -llog
LOCAL_SRC_FILES    =  ../../lynx/Cart.cpp ../../lynx/Memmap.cpp ../../lynx/Mikie.cpp ../../lynx/Ram.cpp ../../lynx/Rom.cpp ../../lynx/Susie.cpp ../../lynx/System.cpp ../../libretro/libretro.cpp
LOCAL_CXXFLAGS = -DANDROID -DARM -D__LIBRETRO__ -DHAVE_STRINGS_H -DHAVE_STDINT_H -DRIGHTSHIFT_IS_SAR
LOCAL_C_INCLUDES = ../../ ../../lynx/ ../../libretro/

include $(BUILD_SHARED_LIBRARY)
