#include <OSD_Thread.hpp>

OSD_Thread::OSD_Thread()
    : myFunc(nullptr),
      myThread(OSD_PTHREAD_NULL),
      myThreadId(0),
      myPriority(0)
{
}

OSD_Thread::OSD_Thread(const OSD_ThreadFunction& func)
    : myFunc(func),
      myThread(OSD_PTHREAD_NULL),
      myThreadId(0),
      myPriority(0)
{
}

OSD_Thread::OSD_Thread(const OSD_Thread& other)
    : myFunc(other.myFunc),
      myThread(OSD_PTHREAD_NULL),
      myThreadId(0)
{
  Assign(other);
}

void OSD_Thread::Assign(const OSD_Thread& other)
{

  myFunc     = other.myFunc;
  myPriority = other.myPriority;

  Detach();

#ifdef _WIN32

  if (other.myThread)
  {
    HANDLE hProc = GetCurrentProcess();
    DuplicateHandle(hProc, other.myThread, hProc, &myThread, 0, TRUE, DUPLICATE_SAME_ACCESS);
  }
#else

  myThread = other.myThread;
#endif

  myThreadId = other.myThreadId;
}

OSD_Thread::~OSD_Thread()
{
  Detach();
}

void OSD_Thread::SetPriority(const int thePriority)
{
  myPriority = thePriority;
#ifdef _WIN32
  if (myThread)
    SetThreadPriority(myThread, thePriority);
#endif
}

void OSD_Thread::SetFunction(const OSD_ThreadFunction& func)
{

  Detach();
  myFunc = func;
}

#ifdef _WIN32
  #include <malloc.h>

struct WNTthread_data
{
  void*              data;
  OSD_ThreadFunction func;
};

static DWORD WINAPI WNTthread_func(LPVOID data)
{
  WNTthread_data* adata = (WNTthread_data*)data;
  void*           ret   = adata->func(adata->data);
  free(adata);
  return PtrToLong(ret);
}
#endif

bool OSD_Thread::Run(void* const data,
#ifdef _WIN32
                     const int WNTStackSize
#else
                     const int
#endif
)
{
  if (!myFunc)
    return false;

  Detach();

#ifdef _WIN32

  WNTthread_data* adata = (WNTthread_data*)malloc(sizeof(WNTthread_data));
  if (!adata)
    return false;
  adata->data = data;
  adata->func = myFunc;

  DWORD aThreadId = DWORD();
  myThread        = CreateThread(NULL, WNTStackSize, WNTthread_func, adata, 0, &aThreadId);
  myThreadId      = aThreadId;
  if (myThread)
    SetThreadPriority(myThread, myPriority);
  else
  {
    memset(adata, 0, sizeof(WNTthread_data));
    free(adata);
  }

#else

  if (pthread_create(&myThread, nullptr, myFunc, data) != 0)
  {
    myThread = OSD_PTHREAD_NULL;
  }
  else
  {
    myThreadId = (Standard_ThreadId)myThread;
  }
#endif
  return myThread != OSD_PTHREAD_NULL;
}

void OSD_Thread::Detach()
{
#ifdef _WIN32

  if (myThread)
    CloseHandle(myThread);

#else

  if (myThread)
    pthread_detach(myThread);

#endif

  myThread   = OSD_PTHREAD_NULL;
  myThreadId = 0;
}

bool OSD_Thread::Wait(void*& theResult)
{

  theResult = nullptr;
  if (!myThread)
  {
    return false;
  }

#ifdef _WIN32

  if (WaitForSingleObject(myThread, INFINITE) != WAIT_OBJECT_0)
  {
    return false;
  }

  DWORD anExitCode;
  if (GetExitCodeThread(myThread, &anExitCode))
  {
    theResult = ULongToPtr(anExitCode);
  }

  CloseHandle(myThread);
  myThread   = OSD_PTHREAD_NULL;
  myThreadId = 0;
  return true;
#else

  if (pthread_join(myThread, &theResult) != 0)
  {
    return false;
  }

  myThread   = OSD_PTHREAD_NULL;
  myThreadId = 0;
  return true;
#endif
}

bool OSD_Thread::Wait(const int theTimeMs, void*& theResult)
{

  theResult = nullptr;
  if (!myThread)
  {
    return false;
  }

#ifdef _WIN32

  DWORD ret = WaitForSingleObject(myThread, theTimeMs);
  if (ret == WAIT_OBJECT_0)
  {
    DWORD anExitCode;
    if (GetExitCodeThread(myThread, &anExitCode))
    {
      theResult = ULongToPtr(anExitCode);
    }

    CloseHandle(myThread);
    myThread   = OSD_PTHREAD_NULL;
    myThreadId = 0;
    return true;
  }
  else if (ret == WAIT_TIMEOUT)
  {
    return false;
  }

  return false;
#else
  #if defined(__GLIBC__) && defined(__GLIBC_PREREQ)
    #if __GLIBC_PREREQ(2, 4)
      #define HAS_TIMED_NP
    #endif
  #endif

  #ifdef HAS_TIMED_NP
  struct timespec aTimeout;
  if (clock_gettime(CLOCK_REALTIME, &aTimeout) == -1)
  {
    return false;
  }

  time_t aSeconds      = (theTimeMs / 1000);
  long   aMicroseconds = (theTimeMs - aSeconds * 1000) * 1000;
  aTimeout.tv_sec += aSeconds;
  aTimeout.tv_nsec += aMicroseconds * 1000;

  if (pthread_timedjoin_np(myThread, &theResult, &aTimeout) != 0)
  {
    return false;
  }

  #else

  (void)theTimeMs;
  if (pthread_join(myThread, &theResult) != 0)
  {
    return false;
  }
  #endif
  myThread   = OSD_PTHREAD_NULL;
  myThreadId = 0;
  return true;
#endif
}

Standard_ThreadId OSD_Thread::GetId() const
{
  return myThreadId;
}

Standard_ThreadId OSD_Thread::Current()
{
#ifdef _WIN32
  return GetCurrentThreadId();
#else
  return (Standard_ThreadId)pthread_self();
#endif
}
