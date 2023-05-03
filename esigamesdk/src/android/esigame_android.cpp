//#define DM_PLATFORM_ANDROID
#if defined(DM_PLATFORM_ANDROID)

#include <jni.h>
#include <dmsdk/dlib/android.h>

#include "../esigamesdk_private.h"
#include "../esigamesdk_callback_private.h"
//#include "esigame_jni.h"
#include "com_defold_esigame_EsiGameSDK.h"

JNIEXPORT void JNICALL Java_com_defold_esigamesdk_EsiGameSDK_esigameAddToQueue(JNIEnv * env, jclass cls, jint jmsg, jstring jjson)
{
    const char* json = env->GetStringUTFChars(jjson, 0);
    dmEsiGameSDK::AddToQueueCallback((dmEsiGameSDK::MessageId)jmsg, json);
    env->ReleaseStringUTFChars(jjson, json);
}

namespace dmEsiGameSDK {

struct EsiGame
{
    jobject        m_EsiGameMaxJNI;

    jmethodID      m_Initialize;

    jmethodID      m_CheckOrder;
    jmethodID      m_LoadVideoAd;
    jmethodID      m_ShowVideo;
    jmethodID      m_LoadInterstitialAd;
    jmethodID      m_ShowInterstitialAd;
    jmethodID      m_GetProducts;
    jmethodID      m_PayNow;
    jmethodID      m_InterstitialIsReady;
    jmethodID      m_InterstitialImageIsReady;
    jmethodID      m_loadBanner;
    jmethodID      m_showBanner;
    jmethodID      m_hiddenBanner;

    jmethodID      m_onUserGuideStep;
    jmethodID      m_setUserLevel;
    jmethodID      m_startLevel;
    jmethodID      m_finishLevel;
    jmethodID      m_failLevel;
    jmethodID      m_startGameLevel;
    jmethodID      m_finishGameLevel;
    jmethodID      m_failGameLevel;

    jmethodID      m_showPolicyPage;

    jmethodID      m_videoIsReady;
    jmethodID      m_getProduct;
    jmethodID      m_onEnterGame;
    jmethodID      m_onEnterLaunchLoading;
    jmethodID      m_event;
    jmethodID      m_eventMap;
    jmethodID      m_getCloudConfig;
};

static EsiGame       g_esigame;

static void CallVoidMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method);
}

static bool CallBooleanMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jboolean return_value = (jboolean)env->CallBooleanMethod(instance, method);
    return JNI_TRUE == return_value;
}

static bool CallBoolMethodInt(jobject instance, jmethodID method, int cint)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jboolean return_value = (jboolean)env->CallBooleanMethod(instance, method, cint);

    return JNI_TRUE == return_value;
}

static bool CallBoolMethodChar(jobject instance, jmethodID method, const char* cstr)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    
    jstring jstr = NULL;
    if (cstr)
    {
        jstr = env->NewStringUTF(cstr);
    }

    jboolean return_value = (jboolean)env->CallBooleanMethod(instance, method, jstr);
    
    if (cstr)
    {
        jstr = env->NewStringUTF(cstr);
    }
    return JNI_TRUE == return_value;
}

static void CallVoidMethodBool(jobject instance, jmethodID method, bool cbool)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method, cbool);
}

static void CallVoidMethodChar(jobject instance, jmethodID method, const char* cstr)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = NULL;
    if (cstr)
    {
        jstr = env->NewStringUTF(cstr);
    }

    env->CallVoidMethod(instance, method, jstr);

    if (cstr)
    {
        env->DeleteLocalRef(jstr);
    }
}

static void CallVoidMethodCharChar(jobject instance, jmethodID method, const char* cstr1, const char* cstr2)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr1 = NULL;
    if (cstr1)
    {
        jstr1 = env->NewStringUTF(cstr1);
    }

    jstring jstr2 = NULL;
    if (cstr2)
    {
        jstr2 = env->NewStringUTF(cstr2);
    }

    env->CallVoidMethod(instance, method, jstr1, jstr2);

    if (cstr1)
    {
        env->DeleteLocalRef(jstr1);
    }

    if (cstr2)
    {
        env->DeleteLocalRef(jstr2);
    }
}


static void CallVoidMethodCharCharChar(jobject instance, jmethodID method, const char* cstr1, const char* cstr2, const char* cstr3)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr1 = NULL;
    if (cstr1)
    {
        jstr1 = env->NewStringUTF(cstr1);
    }

    jstring jstr2 = NULL;
    if (cstr2)
    {
        jstr2 = env->NewStringUTF(cstr2);
    }
    
    jstring jstr3 = NULL;
    if (cstr3)
    {
        jstr3 = env->NewStringUTF(cstr3);
    }

    env->CallVoidMethod(instance, method, jstr1, jstr2, jstr3);

    if (cstr1)
    {
        env->DeleteLocalRef(jstr1);
    }

    if (cstr2)
    {
        env->DeleteLocalRef(jstr2);
    }
    
    if (cstr3)
    {
        env->DeleteLocalRef(jstr3);
    }
}

static void CallVoidMethodCharInt(jobject instance, jmethodID method, const char* cstr, int cint)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    env->CallVoidMethod(instance, method, jstr, cint);
    env->DeleteLocalRef(jstr);
}

static void CallVoidMethodCharCharInt(jobject instance, jmethodID method, const char* cstr, const char* cstr1, int cint)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    jstring jstr1 = env->NewStringUTF(cstr1);
    env->CallVoidMethod(instance, method, jstr, jstr1, cint);
    env->DeleteLocalRef(jstr);
    env->DeleteLocalRef(jstr1);
}

static void CallVoidMethodIntChar(jobject instance, jmethodID method, int cint, const char* cstr)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = NULL;
    if (cstr)
    {
        jstr = env->NewStringUTF(cstr);
    }

    env->CallVoidMethod(instance, method, cint, jstr);

    if (cstr)
    {
        env->DeleteLocalRef(jstr);
    }
}

static void CallVoidMethodInt(jobject instance, jmethodID method, int cint)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method, cint);
}

static void InitJNIMethods(JNIEnv* env, jclass cls)
{
    g_esigame.m_Initialize               = env->GetMethodID(cls, "initialize", "()V");

    //g_esigame.m_CheckOrder               = env->GetMethodID(cls, "checkOrder", "()V");
    g_esigame.m_LoadVideoAd              = env->GetMethodID(cls, "loadVideoAd", "()V");
    g_esigame.m_ShowVideo                = env->GetMethodID(cls, "showVideo", "(Ljava/lang/String;)V");
    g_esigame.m_LoadInterstitialAd       = env->GetMethodID(cls, "loadInterstitialAd", "()V");
    g_esigame.m_ShowInterstitialAd       = env->GetMethodID(cls, "showInterstitialAd", "()V");
    g_esigame.m_GetProducts              = env->GetMethodID(cls, "getProducts", "(Ljava/lang/String;)V");
    g_esigame.m_PayNow                   = env->GetMethodID(cls, "payNow", "(Ljava/lang/String;)V");
    g_esigame.m_InterstitialIsReady      = env->GetMethodID(cls, "interstitialIsReady", "()Z");
    //g_esigame.m_InterstitialImageIsReady = env->GetMethodID(cls, "interstitialImageIsReady", "()Z");
    //g_esigame.m_loadBanner               = env->GetMethodID(cls, "loadBanner", "()V");
    g_esigame.m_showBanner               = env->GetMethodID(cls, "showBanner", "(I)V");
    g_esigame.m_hiddenBanner             = env->GetMethodID(cls, "hiddenBanner", "()V");

    g_esigame.m_onUserGuideStep = env->GetMethodID(cls, "onUserGuideStep", "(Ljava/lang/String;)V");
    g_esigame.m_setUserLevel = env->GetMethodID(cls, "setUserLevel", "(I)V");
    g_esigame.m_startLevel = env->GetMethodID(cls, "startLevel", "(Ljava/lang/String;)V");
    g_esigame.m_finishLevel = env->GetMethodID(cls, "finishLevel", "(Ljava/lang/String;)V");
    g_esigame.m_failLevel = env->GetMethodID(cls, "failLevel", "(Ljava/lang/String;)V");
    //g_esigame.m_startGameLevel = env->GetMethodID(cls, "startGameLevel", "(Ljava/lang/String;)V");
    //g_esigame.m_finishGameLevel = env->GetMethodID(cls, "finishGameLevel", "(Ljava/lang/String;)V");
    //g_esigame.m_failGameLevel = env->GetMethodID(cls, "failGameLevel", "(Ljava/lang/String;)V");

//    g_esigame.m_showPolicyPage = env->GetMethodID(cls, "showPolicyPage", "()V");

    g_esigame.m_videoIsReady = env->GetMethodID(cls, "videoIsReady", "()Z");
    g_esigame.m_getProduct = env->GetMethodID(cls, "getProduct", "(Ljava/lang/String;)V");
    g_esigame.m_onEnterGame = env->GetMethodID(cls, "onEnterGame", "()V");
    g_esigame.m_onEnterLaunchLoading = env->GetMethodID(cls, "onEnterLaunchLoading", "()V");
    g_esigame.m_event = env->GetMethodID(cls, "event", "(Ljava/lang/String;)V");
    g_esigame.m_eventMap = env->GetMethodID(cls, "eventMap", "(Ljava/lang/String;Ljava/lang/String;)V");
    g_esigame.m_getCloudConfig = env->GetMethodID(cls, "getCloudConfig", "(Ljava/lang/String;Ljava/lang/String;)V");
}

void Initialize_Ext()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com/defold/esigamesdk/EsiGameSDK");

    InitJNIMethods(env, cls);

    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");

    g_esigame.m_EsiGameMaxJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
}

void Initialize()
{
    CallVoidMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_Initialize);
}

void CheckOrder()
{
    CallVoidMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_CheckOrder);
}

void LoadVideoAd()
{
    CallVoidMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_LoadVideoAd);
}

void ShowVideo(const char* unitId)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_ShowVideo, unitId);
}

void LoadInterstitialAd()
{
    CallVoidMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_LoadInterstitialAd);
}

void ShowInterstitialAd()
{
    CallVoidMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_ShowInterstitialAd);
}

void GetProducts(const char* product_ids)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_GetProducts, product_ids);
}

void PayNow(const char* unitId)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_PayNow, unitId);
}

bool InterstitialIsReady()
{
    return CallBooleanMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_InterstitialIsReady);
}

bool InterstitialImageIsReady()
{
    return CallBooleanMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_InterstitialImageIsReady);
}

bool loadBanner()
{
    return CallBooleanMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_loadBanner);
}

void showBanner(int bannerLocation)
{
    CallVoidMethodInt(g_esigame.m_EsiGameMaxJNI, g_esigame.m_showBanner, bannerLocation);
}

bool hiddenBanner()
{
    return CallBooleanMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_hiddenBanner);
}

void onUserGuideStep(const char* step)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_onUserGuideStep, step);
}

void setUserLevel(int level)
{
    CallVoidMethodInt(g_esigame.m_EsiGameMaxJNI, g_esigame.m_setUserLevel, level);
}

void startLevel(const char* level)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_startLevel, level);
}

void finishLevel(const char* level)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_finishLevel, level);
}

void failLevel(const char* level)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_failLevel, level);
}

void startGameLevel(const char* level)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_startGameLevel, level);
}

void finishGameLevel(const char* level)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_finishGameLevel, level);
}

void failGameLevel(const char* level)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_failGameLevel, level);
}
/*
bool showPolicyPage()
{
    return CallBooleanMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_showPolicyPage);
}
*/

bool videoIsReady()
{
    return CallBooleanMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_videoIsReady);
}

void getProduct(const char* product_id)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_getProduct, product_id);
}

void onEnterGame()
{
    CallVoidMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_onEnterGame);
}

void onEnterLaunchLoading()
{
    CallVoidMethod(g_esigame.m_EsiGameMaxJNI, g_esigame.m_onEnterLaunchLoading);
}

void event_(const char* event_id)
{
    CallVoidMethodChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_event, event_id);
}

void eventMap(const char* event_id, const char* event_data)
{
    CallVoidMethodCharChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_eventMap, event_id, event_data);
}

void getCloudConfig(const char* config_key, const char* default_value)
{
    CallVoidMethodCharChar(g_esigame.m_EsiGameMaxJNI, g_esigame.m_getCloudConfig, config_key, default_value);
}

}//namespace dmEsiGameSDK

#endif
