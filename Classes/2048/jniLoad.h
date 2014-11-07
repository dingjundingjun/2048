#ifndef JNILOAD_H_
#define JNILOAD_H_

#include "cocos2d.h"
#include "cocos-ext.h"

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#if 0

#include "JniHelper.h"
#include <android/log.h>
#include <string.h>

#define MY_LOG_TAG "JNI_LOG"
#define MY_LOGI(...) __android_log_print(ANDROID_LOG_INFO, MY_LOG_TAG, __VA_ARGS__)
#define MY_LOGE(...) __android_log_print(ANDROID_LOG_ERROR, MY_LOG_TAG, __VA_ARGS__)

int jniRegisterNativeMethods(JNIEnv* env, const char* className,
		const JNINativeMethod* gMethods, int numMethods);

#endif


#endif 
