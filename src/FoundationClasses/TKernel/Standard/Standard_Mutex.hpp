#pragma once

#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_ErrorHandler.hpp>
#include <NCollection_Shared.hpp>

#if defined(_WIN32)
  #include <windows.h>
#else
  #include <pthread.h>
  #include <unistd.h>
  #include <time.h>
#endif

class Standard_Mutex : public Standard_ErrorHandler::Callback
{
public:
  class Sentry
  {
  public:
    Sentry(Standard_Mutex& theMutex)
        : myMutex(&theMutex)
    {
      Lock();
    }

    Sentry(Standard_Mutex* theMutex)
        : myMutex(theMutex)
    {
      if (myMutex != nullptr)
      {
        Lock();
      }
    }

    ~Sentry()
    {
      if (myMutex != nullptr)
      {
        Unlock();
      }
    }

  private:
    void Lock()
    {
      myMutex->Lock();
      myMutex->RegisterCallback();
    }

    void Unlock()
    {
      myMutex->UnregisterCallback();
      myMutex->Unlock();
    }

    Sentry(const Sentry&) = delete;

    Sentry& operator=(const Sentry&) = delete;

  private:
    Standard_Mutex* myMutex;
  };

public:
  Standard_EXPORT Standard_Mutex();

  Standard_EXPORT ~Standard_Mutex() override;

  Standard_EXPORT void Lock();

  Standard_EXPORT bool TryLock();

  void Unlock();

private:
  Standard_EXPORT void DestroyCallback() override;

  Standard_Mutex(const Standard_Mutex&) = delete;

  Standard_Mutex& operator=(const Standard_Mutex&) = delete;

private:
#if (defined(_WIN32) || defined(__WIN32__))
  CRITICAL_SECTION myMutex;
#else
  pthread_mutex_t myMutex;
#endif
};

typedef NCollection_Shared<Standard_Mutex> Standard_HMutex;

inline void Standard_Mutex::Unlock()
{
#if (defined(_WIN32) || defined(__WIN32__))
  LeaveCriticalSection(&myMutex);
#else
  pthread_mutex_unlock(&myMutex);
#endif
}
