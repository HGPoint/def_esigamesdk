#include <jni.h>
/* Header for class com_defold_esigame_EsiGameSDK */

#ifndef COM_DEFOLD_ESIGAME_ESIGAMEJNI_H
#define COM_DEFOLD_ESIGAME_ESIGAMEJNI_H
#ifdef __cplusplus
extern "C" {
#endif
	/*
	* Class:     com_defold_esigame_EsiGameSDK
	* Method:    esigameAddToQueue_first_arg
	* Signature: (ILjava/lang/String;I)V
	*/
	JNIEXPORT void JNICALL Java_com_defold_esigamesdk_EsiGameSDK_esigameAddToQueue
		(JNIEnv *, jclass, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif
