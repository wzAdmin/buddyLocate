include $(LOCAL_PATH)/RakNet.mk

include $(CLEAR_VARS)
LOCAL_MODULE := amapv3
LOCAL_SRC_FILES := libamapv3.so
include $(PREBUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -DANDROID
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../RakNet/include \
					$(LOCAL_PATH)/../../../Common \
					$(LOCAL_PATH)/../../Source
LOCAL_MODULE := Client
LOCAL_SRC_FILES := $(call all-cpp-files-under,../../Source) \
					$(call all-cpp-files-under,Source) \
					$(call all-cpp-files-under,../../../Common) 
LOCAL_LDLIBS := -llog
LOCAL_STATIC_LIBRARIES := RakNet
include $(BUILD_SHARED_LIBRARY)
