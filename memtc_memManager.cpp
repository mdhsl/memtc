#include <jni.h>
#include "memtc_memManager.h"
#include <iostream>
#include <mutex>
#include "MemoryManager.h"
#define MEMTC_NULL_EXCEPTION ((int) 0)
#  define _memtc_long_to_addr(_val)   ((void *)(_val))
#  define _addr_to_memtc_long(_addr)  ((long)(_addr))

using namespace std;

using std::string;
using std::cout;
using std::endl;

static mutex __class_LOADER_lock;

static jclass memtc_manager_CLS = NULL;
static jfieldID memtc_manager_PTR = NULL;
static jmethodID memtc_manager_INIT_PTR = NULL;



static void memtc_manager_LOADER(JNIEnv *__env)
{
  jclass lcl_class = __env->FindClass("memtc/MemtcJNI");
  if (lcl_class==NULL) throw MEMTC_NULL_EXCEPTION;
  jclass memtc_class = (jclass) __env->NewGlobalRef(lcl_class);
  __env->DeleteLocalRef(lcl_class);
  jfieldID memtc_field = __env->GetFieldID(memtc_class,"_native_ptr","J");
  if (memtc_field==NULL) throw MEMTC_NULL_EXCEPTION;
  __class_LOADER_lock.lock();
  if (memtc_manager_CLS == NULL)
    {
      memtc_manager_PTR = memtc_field;
      memtc_manager_CLS = memtc_class;
      memtc_class = NULL;
    }
  __class_LOADER_lock.unlock();
  if (memtc_class != NULL)
    __env->DeleteGlobalRef(memtc_class);
}

JNIEXPORT jlong JNICALL Java_memtc_MemtcJNI_Native_1create__(JNIEnv *__env, jclass this_class)
{
  try {
    MemoryManager *self = new MemoryManager();
    return ((jlong) _addr_to_memtc_long(self)) | ((jlong) 1);
  } catch(std::bad_alloc &)
  { cout << "bad allocation" << endl; }
  catch(...) {};
  return (jlong) 0;
}

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_Native_1destroy(JNIEnv *__env, jobject _self)
{
    if (memtc_manager_CLS==NULL)
      memtc_manager_LOADER(__env);
    jlong self_ref = __env->GetLongField(_self,memtc_manager_PTR);
    if (self_ref == 0) return;
    __env->SetLongField(_self,memtc_manager_PTR,0);
    if ((self_ref & ((jlong) 1)) != 0)
      {
        MemoryManager *self = (MemoryManager *) _memtc_long_to_addr(self_ref - ((jlong) 1));
        delete self;
      }
}

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_Native_1init_1class(JNIEnv *__env, jclass this_class)
{
  if (memtc_manager_CLS != NULL) return;
  try {
    memtc_manager_LOADER(__env);
  } catch(...) {};
}

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_TryRelease(JNIEnv *__env, jobject _self, jboolean force){
    try {
        if (memtc_manager_CLS==NULL)
          memtc_manager_LOADER(__env);
        MemoryManager *self = (MemoryManager *)
          _memtc_long_to_addr(__env->GetLongField(_self,memtc_manager_PTR) & ~((jlong) 1));
        // todo if NULL -> throw exception
        self->tryRelease(force);

  } catch (...)
  {cout << "exception 3" << endl; }
}

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_SetMaxBytes(JNIEnv *__env, jobject _self, jlong bytes) {
    try {
        if (memtc_manager_CLS==NULL)
            memtc_manager_LOADER(__env);

        MemoryManager *self = (MemoryManager *)
        _memtc_long_to_addr(__env->GetLongField(_self,memtc_manager_PTR) & ~((jlong) 1));
        // todo if NULL -> throw exception
        self->setMaxBytes(bytes);

    } catch (...)
    {cout << "exception 3" << endl; }
}

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_SetMinBytes(JNIEnv *__env, jobject _self, jlong bytes) {
    try {
        if (memtc_manager_CLS==NULL)
            memtc_manager_LOADER(__env);

        MemoryManager *self = (MemoryManager *)
                _memtc_long_to_addr(__env->GetLongField(_self,memtc_manager_PTR) & ~((jlong) 1));
        // todo if NULL -> throw exception
        self->setMinBytes(bytes);

    } catch (...)
    {cout << "exception 3" << endl; }
}

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_SetCriticalBytes(JNIEnv *__env, jobject _self, jlong bytes) {
    try {
        if (memtc_manager_CLS==NULL)
            memtc_manager_LOADER(__env);

        MemoryManager *self = (MemoryManager *)
                _memtc_long_to_addr(__env->GetLongField(_self,memtc_manager_PTR) & ~((jlong) 1));
        // todo if NULL -> throw exception
        self->setCriticalBytes(bytes);
    } catch (...)
    {cout << "exception 3" << endl; }
}

JNIEXPORT void JNICALL Java_memtc_MemtcJNI_DisplayMemoryInfos(JNIEnv *__env, jobject _self) {
    try {
        if (memtc_manager_CLS==NULL)
            memtc_manager_LOADER(__env);

        MemoryManager *self = (MemoryManager *)
                _memtc_long_to_addr(__env->GetLongField(_self,memtc_manager_PTR) & ~((jlong) 1));
        // todo if NULL -> throw exception
        self->displayMemoryInfos();

    } catch (...)
    {cout << "exception 3" << endl; }
}