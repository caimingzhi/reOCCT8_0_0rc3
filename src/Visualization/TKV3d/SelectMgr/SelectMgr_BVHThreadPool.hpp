#pragma once

#include <Standard_Transient.hpp>
#include <OSD_Thread.hpp>
#include <Select3D_SensitiveEntity.hpp>
#include <Standard_Condition.hpp>
#include <Message_Messenger.hpp>

#include <mutex>

class SelectMgr_BVHThreadPool : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(SelectMgr_BVHThreadPool, Standard_Transient)
public:
  Standard_EXPORT SelectMgr_BVHThreadPool(int theNbThreads);

  Standard_EXPORT ~SelectMgr_BVHThreadPool() override;

public:
  class BVHThread : public OSD_Thread
  {
    friend class SelectMgr_BVHThreadPool;

  public:
    BVHThread()
        : myPool(nullptr),

          myToCatchFpe(false)
    {
    }

    BVHThread(const BVHThread& theOther)
        : OSD_Thread(theOther),
          myPool(theOther.myPool),

          myToCatchFpe(theOther.myToCatchFpe)
    {
    }

    std::mutex& BVHMutex() { return myMutex; }

    BVHThread& operator=(const BVHThread& theCopy)
    {
      Assign(theCopy);
      return *this;
    }

    void Assign(const BVHThread& theCopy)
    {
      OSD_Thread::Assign(theCopy);
      myPool       = theCopy.myPool;
      myToCatchFpe = theCopy.myToCatchFpe;
    }

  private:
    void performThread();

    static void* runThread(void* theTask);

  private:
    SelectMgr_BVHThreadPool* myPool;
    std::mutex               myMutex;
    bool                     myToCatchFpe;
  };

public:
  Standard_EXPORT void AddEntity(const occ::handle<Select3D_SensitiveEntity>& theEntity);

  Standard_EXPORT void StopThreads();

  Standard_EXPORT void WaitThreads();

  NCollection_Array1<BVHThread>& Threads() { return myBVHThreads; }

public:
  class Sentry
  {
  public:
    Sentry(const occ::handle<SelectMgr_BVHThreadPool>& thePool)
        : myPool(thePool)
    {
      Lock();
    }

    ~Sentry() { Unlock(); }

    void Lock()
    {
      if (!myPool.IsNull())
      {
        for (int i = myPool->Threads().Lower(); i <= myPool->Threads().Upper(); ++i)
        {
          myPool->Threads().ChangeValue(i).BVHMutex().lock();
        }
      }
    }

    void Unlock()
    {
      if (!myPool.IsNull())
      {
        for (int i = myPool->Threads().Lower(); i <= myPool->Threads().Upper(); ++i)
        {
          myPool->Threads().ChangeValue(i).BVHMutex().unlock();
        }
      }
    }

    Sentry(const Sentry&);

    Sentry& operator=(const Sentry&);

  private:
    occ::handle<SelectMgr_BVHThreadPool> myPool;
  };

protected:
  NCollection_List<occ::handle<Select3D_SensitiveEntity>> myBVHToBuildList;
  NCollection_Array1<BVHThread>                           myBVHThreads;
  bool                                                    myToStopBVHThread;
  std::mutex                                              myBVHListMutex;
  Standard_Condition                                      myWakeEvent;
  Standard_Condition                                      myIdleEvent;
  bool                                                    myIsStarted;
};
