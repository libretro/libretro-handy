LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

GIT_VERSION := " $(shell git rev-parse --short HEAD || echo unknown)"
ifneq ($(GIT_VERSION)," unknown")
	LOCAL_CXXFLAGS += -DGIT_VERSION=\"$(GIT_VERSION)\"
endif

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
LOCAL_LDLIBS    += -lz 
CORE_DIR := ..

include $(CORE_DIR)/Makefile.common

LOCAL_SRC_FILES    =  $(SOURCES_CXX)

LOCAL_CXXFLAGS += -DANDROID -DARM -D__LIBRETRO__ -DHAVE_STRINGS_H -DHAVE_STDINT_H -DRIGHTSHIFT_IS_SAR -DWANT_CRC32

LOCAL_C_INCLUDES = $(CORE_DIR) $(CORE_DIR)/lynx $(CORE_DIR)/libretro

include $(BUILD_SHARED_LIBRARY)
