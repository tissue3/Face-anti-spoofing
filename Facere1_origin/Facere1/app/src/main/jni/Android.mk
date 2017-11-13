LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
OPENCV_LIB_TYPE:=STATIC
ifeq ("$(wildcard $(OPENCV_MK_PATH))","")

include C:\Users\CodeMonkeyCui\Desktop\OpenCV-2.4.9-android-sdk\OpenCV-2.4.9-android-sdk\sdk\native\jni\OpenCV.mk
else
include $(OPENCV_MK_PATH)
endif

LOCAL_MODULE := ImgFun
LOCAL_SRC_FILES := ImgFun.cpp
LOCAL_LDLIBS += -lm -llog
include $(BUILD_SHARED_LIBRARY)