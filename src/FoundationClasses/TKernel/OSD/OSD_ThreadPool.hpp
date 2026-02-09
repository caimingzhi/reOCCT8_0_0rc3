#pragma once

#include <NCollection_Array1.hpp>
#include <OSD_Thread.hpp>
#include <Standard_Condition.hpp>

#include <Standard_ProgramError.hpp>

#include <atomic>
#include <optional>

class OSD_ThreadPool : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(OSD_ThreadPool, Standard_Transient)
public:
  Standard_EXPORT static const occ::handle<OSD_ThreadPool>& DefaultPool(int theNbThreads = -1);

public:
  Standard_EXPORT OSD_ThreadPool(int theNbThreads = -1);

  Standard_EXPORT ~OSD_ThreadPool() override;

  bool HasThreads() const { return NbThreads() >= 2; }

  int LowerThreadIndex() const { return 0; }

  int UpperThreadIndex() const { return LowerThreadIndex() + myThreads.Size(); }

  int NbThreads() const { return myThreads.Size() + 1; }

  int NbDefaultThreadsToLaunch() const { return myNbDefThreads; }

  void SetNbDefaultThreadsToLaunch(int theNbThreads) { myNbDefThreads = theNbThreads; }

  Standard_EXPORT bool IsInUse();

  Standard_EXPORT void Init(int theNbThreads);

protected:
  class JobInterface
  {
  public:
    virtual void Perform(int theThreadIndex) = 0;
  };

  class EnumeratedThread : public OSD_Thread
  {
    friend class OSD_ThreadPool;

  public:
    EnumeratedThread(bool theIsSelfThread = false)
        : myPool(nullptr),
          myJob(nullptr),
          myWakeEvent(false),
          myIdleEvent(false),
          myThreadIndex(0),
          myUsageCounter(0),
          myIsStarted(false),
          myToCatchFpe(false),
          myIsSelfThread(theIsSelfThread)
    {
    }

    Standard_EXPORT bool Lock();

    Standard_EXPORT void Free();

    Standard_EXPORT void WakeUp(JobInterface* theJob, bool theToCatchFpe);

    Standard_EXPORT void WaitIdle();

  public:
    EnumeratedThread(const EnumeratedThread& theCopy)
        : OSD_Thread(theCopy),
          myPool(nullptr),
          myJob(nullptr),
          myWakeEvent(false),
          myIdleEvent(false),
          myThreadIndex(0),
          myUsageCounter(0),
          myIsStarted(false),
          myToCatchFpe(false),
          myIsSelfThread(false)
    {
      Assign(theCopy);
    }

    EnumeratedThread& operator=(const EnumeratedThread& theCopy)
    {
      Assign(theCopy);
      return *this;
    }

    void Assign(const EnumeratedThread& theCopy)
    {
      OSD_Thread::Assign(theCopy);
      myPool         = theCopy.myPool;
      myJob          = theCopy.myJob;
      myThreadIndex  = theCopy.myThreadIndex;
      myToCatchFpe   = theCopy.myToCatchFpe;
      myIsSelfThread = theCopy.myIsSelfThread;
    }

  private:
    void performThread();

    static void* runThread(void* theTask);

  private:
    OSD_ThreadPool*                      myPool;
    JobInterface*                        myJob;
    std::optional<Standard_ProgramError> myFailure;
    Standard_Condition                   myWakeEvent;
    Standard_Condition                   myIdleEvent;
    int                                  myThreadIndex;
    std::atomic<int>                     myUsageCounter;
    bool                                 myIsStarted;
    bool                                 myToCatchFpe;
    bool                                 myIsSelfThread;
  };

public:
  class Launcher
  {
  public:
    Standard_EXPORT Launcher(OSD_ThreadPool& thePool, int theMaxThreads = -1);

    ~Launcher() { Release(); }

    bool HasThreads() const { return myNbThreads >= 2; }

    int NbThreads() const { return myNbThreads; }

    int LowerThreadIndex() const { return 0; }

    int UpperThreadIndex() const { return LowerThreadIndex() + myNbThreads - 1; }

    template <typename Functor>
    void Perform(int theBegin, int theEnd, const Functor& theFunctor)
    {
      JobRange     aData(theBegin, theEnd);
      Job<Functor> aJob(theFunctor, aData);
      perform(aJob);
    }

    Standard_EXPORT void Release();

  protected:
    Standard_EXPORT void perform(JobInterface& theJob);

    Standard_EXPORT void run(JobInterface& theJob);

    Standard_EXPORT void wait();

  private:
    Launcher(const Launcher& theCopy)            = delete;
    Launcher& operator=(const Launcher& theCopy) = delete;

  private:
    NCollection_Array1<EnumeratedThread*> myThreads;

    EnumeratedThread mySelfThread;
    int              myNbThreads;
  };

protected:
  class JobRange
  {
  public:
    JobRange(const int& theBegin, const int& theEnd)
        : myBegin(theBegin),
          myEnd(theEnd),
          myIt(theBegin)
    {
    }

    const int& Begin() const { return myBegin; }

    const int& End() const { return myEnd; }

    int It() const { return myIt.fetch_add(1); }

  private:
    JobRange(const JobRange& theCopy)            = delete;
    JobRange& operator=(const JobRange& theCopy) = delete;

  private:
    const int&               myBegin;
    const int&               myEnd;
    mutable std::atomic<int> myIt;
  };

  template <typename FunctorT>
  class Job : public JobInterface
  {
  public:
    Job(const FunctorT& thePerformer, JobRange& theRange)
        : myPerformer(thePerformer),
          myRange(theRange)
    {
    }

    void Perform(int theThreadIndex) override
    {
      for (int anIter = myRange.It(); anIter < myRange.End(); anIter = myRange.It())
      {
        myPerformer(theThreadIndex, anIter);
      }
    }

  private:
    Job(const Job& theCopy)            = delete;
    Job& operator=(const Job& theCopy) = delete;

  private:
    const FunctorT& myPerformer;
    const JobRange& myRange;
  };

  void release();

  static void performJob(std::optional<Standard_ProgramError>& theFailure,
                         OSD_ThreadPool::JobInterface*         theJob,
                         int                                   theThreadIndex);

private:
  OSD_ThreadPool(const OSD_ThreadPool& theCopy) = delete;

  OSD_ThreadPool& operator=(const OSD_ThreadPool& theCopy) = delete;

private:
  NCollection_Array1<EnumeratedThread> myThreads;

  int  myNbDefThreads;
  bool myShutDown;
};
