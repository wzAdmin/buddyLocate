LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := RakNet
LOCAL_CFLAGS += -DANDROID
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../RakNet/include
MY_PREFIX := $(LOCAL_PATH)/../../../RakNet/Source/
MY_SOURCES := $(wildcard $(MY_PREFIX)*.cpp)
LOCAL_SRC_FILES += $(MY_SOURCES:$(MY_PREFIX)%=../../../RakNet/Source/%) 
include $(BUILD_SHARED_LIBRARY)

