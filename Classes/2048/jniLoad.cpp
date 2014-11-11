#include "jniLoad.h"
using namespace std;

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#if 0

int register_org_join_CocosNative(JNIEnv *env);

int jniRegisterNativeMethods(JNIEnv* env, const char* className,
		const JNINativeMethod* gMethods, int numMethods) {

	jclass clazz;

	MY_LOGI("Registering %s natives\n", className);
	clazz = env->FindClass(className);

	if (clazz == NULL) {
		MY_LOGE("Native registration unable to find class '%s'\n", className);
		return JNI_ERR;
	}
	if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
		MY_LOGE("RegisterNatives failed for '%s'\n", className);
		return JNI_ERR;
	}
	return JNI_OK;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = JNI_ERR;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
    	MY_LOGE("GetEnv failed!");
        return result;
    }

    MY_LOGI("loading . . .");

    if(register_org_join_CocosNative(env) != JNI_OK) {
    	MY_LOGE("can't load org_join_skia_SkiaView");
        goto end;
    }
    /**
     * register others
     */
    MY_LOGI("loaded");

    result = JNI_VERSION_1_4;
end:
    return result;
}


#endif




