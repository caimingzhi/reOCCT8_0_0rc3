#include <Standard_Mutex.hpp>

Standard_Mutex::Standard_Mutex()
{
#if (defined(_WIN32) || defined(__WIN32__))
  InitializeCriticalSection(&myMutex);
#else
  pthread_mutexattr_t anAttr;
  pthread_mutexattr_init(&anAttr);
  pthread_mutexattr_settype(&anAttr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&myMutex, &anAttr);
  pthread_mutexattr_destroy(&anAttr);
#endif
}

Standard_Mutex::~Standard_Mutex()
{
#if (defined(_WIN32) || defined(__WIN32__))
  DeleteCriticalSection(&myMutex);
#else
  pthread_mutex_destroy(&myMutex);
#endif
}

void Standard_Mutex::Lock()
{
#if (defined(_WIN32) || defined(__WIN32__))
  EnterCriticalSection(&myMutex);
#else
  pthread_mutex_lock(&myMutex);
#endif
}

bool Standard_Mutex::TryLock()
{
#if (defined(_WIN32) || defined(__WIN32__))
  return (TryEnterCriticalSection(&myMutex) != 0);
#else
  return (pthread_mutex_trylock(&myMutex) != EBUSY);
#endif
}

void Standard_Mutex::DestroyCallback()
{
  UnregisterCallback();
  Unlock();
}
