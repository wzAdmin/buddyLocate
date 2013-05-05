include $(CLEAR_VARS)
include jni/Android.mk
LOCAL_JNI_SHARED_LIBRARIES := libamapv3.so
include $(BUILD_SHARED_LIBRARY)