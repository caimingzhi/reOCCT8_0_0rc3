#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
typedef void* (*OSD_ThreadFunction)(void* data);

#ifdef _WIN32

  #include <windows.h>
typedef HANDLE OSD_PThread;
  #define OSD_PTHREAD_NULL nullptr

#else

  #include <pthread.h>
typedef pthread_t OSD_PThread;

  #define OSD_PTHREAD_NULL 0

#endif

#include <Standard_ThreadId.hpp>
#include <Standard_Boolean.hpp>

class OSD_Thread
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_Thread();

  Standard_EXPORT OSD_Thread(const OSD_ThreadFunction& func);

  Standard_EXPORT OSD_Thread(const OSD_Thread& other);

  Standard_EXPORT void Assign(const OSD_Thread& other);

  void operator=(const OSD_Thread& other) { Assign(other); }

  Standard_EXPORT ~OSD_Thread();

  Standard_EXPORT void SetPriority(const int thePriority);

  Standard_EXPORT void SetFunction(const OSD_ThreadFunction& func);

  Standard_EXPORT bool Run(void* const data = nullptr, const int WNTStackSize = 0);

  Standard_EXPORT void Detach();

  bool Wait()
  {
    void* aRes = nullptr;
    return Wait(aRes);
  }

  Standard_EXPORT bool Wait(void*& theResult);

  Standard_EXPORT bool Wait(const int time, void*& theResult);

  Standard_EXPORT Standard_ThreadId GetId() const;

  Standard_EXPORT static Standard_ThreadId Current();

private:
  OSD_ThreadFunction myFunc;
  OSD_PThread        myThread;
  Standard_ThreadId  myThreadId;
  int                myPriority;
};
