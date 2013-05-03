
include $(CLEAR_VARS)
LOCAL_CFLAGS += -DANDROID
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../RakNet/include
LOCAL_MODULE := RakNet
LOCAL_SRC_FILES := $(call all-cpp-files-under,../../../RakNet/Source) 

LOCAL_LDLIBS := -lz -lm -llog
	
include $(BUILD_SHARED_LIBRARY)