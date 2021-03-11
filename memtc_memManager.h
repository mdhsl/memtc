#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_Native_1init_1class(JNIEnv *__env, jclass this_class);

JNIEXPORT jlong JNICALL  Java_memtc_MemtcJNI_Native_1create__(JNIEnv *__env, jclass this_class);

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_Native_1destroy(JNIEnv *__env, jobject _self);

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_TryRelease(JNIEnv *__env, jobject _self, jboolean force);

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_SetMaxBytes(JNIEnv *__env, jobject _self, jlong bytes);

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_SetMinBytes(JNIEnv *__env, jobject _self, jlong bytes);

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_SetCriticalBytes(JNIEnv *__env, jobject _self, jlong bytes);

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_DisplayMemoryInfos(JNIEnv *__env, jobject _self);

#ifdef __cplusplus
}
#endif
