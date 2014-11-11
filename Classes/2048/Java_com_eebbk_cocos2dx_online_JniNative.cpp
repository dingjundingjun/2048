#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "JniHelper.h"
#include <jni.h>
#include "jniLoad.h"
#include "Config.h"
using namespace cocos2d;

#define  LOG_TAG    "Java_com_eebbk_cocos2dx_online_JniNative"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" {

    JNIEXPORT void JNICALL Java_com_eebbk_cocos2dx_online_JniNative_updateChartCallBack(JNIEnv* env, jobject thiz, jint rankNumber, jint totalScore ) {

		LOGD(" updateChartCallBack: rankNumber ===%d,totalScore===%d",rankNumber,totalScore);

    }

    //com.eebbk.cocos2dx.activity.GameMain.setSuccessData
    JNIEXPORT jint JNICALL Java_com_eebbk_cocos2dx_activity_GameMain_set(JNIEnv *env, jobject obj,int rank,int score)
    {
    	LOGD(" rank ==================== %d",rank);
    	LOGD(" score ==================== %d",score);
    	Config::sharedConfig()->setRanking(rank);
    	Config::sharedConfig()->setScore(score);
    	return 0;
    }

}

#endif
