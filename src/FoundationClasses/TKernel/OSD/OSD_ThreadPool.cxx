#include <OSD_ThreadPool.hpp>

#include <OSD.hpp>
#include <OSD_Parallel.hpp>
#include <Standard_ErrorHandler.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(System::os::OSD_ThreadPool, Standard_Transient)

bool System::os::OSD_ThreadPool::EnumeratedThread::Lock()
{
  return myUsageCounter.exchange(1) == 0;
}

void System::os::OSD_ThreadPool::EnumeratedThread::Free()
{
  myUsageCounter.store(0);
}

void System::os::OSD_ThreadPool::EnumeratedThread::WakeUp(JobInterface* theJob, bool theToCatchFpe)
{
  myJob        = theJob;
  myToCatchFpe = theToCatchFpe;
  if (myIsSelfThread)
  {
    if (theJob != nullptr)
    {
      System::os::OSD_ThreadPool::performJob(myFailure, myJob, myThreadIndex);
    }
    return;
  }

  myWakeEvent.Set();
  if (theJob != nullptr && !myIsStarted)
  {
    myIsStarted = true;
    Run(this);
  }
}

void System::os::OSD_ThreadPool::EnumeratedThread::WaitIdle()
{
  if (!myIsSelfThread)
  {
    myIdleEvent.Wait();
    myIdleEvent.Reset();
  }
}

const occ::handle<System::os::OSD_ThreadPool>& System::os::OSD_ThreadPool::DefaultPool(int theNbThreads)
{
  static const occ::handle<System::os::OSD_ThreadPool> THE_GLOBAL_POOL = new System::os::OSD_ThreadPool(theNbThreads);
  return THE_GLOBAL_POOL;
}

System::os::OSD_ThreadPool::OSD_ThreadPool(int theNbThreads)
    : myNbDefThreads(0),
      myShutDown(false)
{
  Init(theNbThreads);
  myNbDefThreads = NbThreads();
}

bool System::os::OSD_ThreadPool::IsInUse()
{
  for (NCollection_Array1<EnumeratedThread>::Iterator aThreadIter(myThreads); aThreadIter.More();
       aThreadIter.Next())
  {
    EnumeratedThread& aThread = aThreadIter.ChangeValue();
    if (!aThread.Lock())
    {
      return true;
    }
    aThread.Free();
  }
  return false;
}

void System::os::OSD_ThreadPool::Init(int theNbThreads)
{
  const int aNbThreads =
    std::max(0, (theNbThreads > 0 ? theNbThreads : System::os::OSD_Parallel::NbLogicalProcessors()) - 1);
  if (myThreads.Size() == aNbThreads)
  {
    return;
  }

  if (!myThreads.IsEmpty())
  {
    NCollection_Array1<EnumeratedThread*> aLockThreads(myThreads.Lower(), myThreads.Upper());
    aLockThreads.Init(nullptr);
    int aThreadIndex = myThreads.Lower();
    for (NCollection_Array1<EnumeratedThread>::Iterator aThreadIter(myThreads); aThreadIter.More();
         aThreadIter.Next())
    {
      EnumeratedThread& aThread = aThreadIter.ChangeValue();
      if (!aThread.Lock())
      {
        for (NCollection_Array1<EnumeratedThread*>::Iterator aLockThreadIter(aLockThreads);
             aLockThreadIter.More() && aLockThreadIter.Value() != nullptr;
             aLockThreadIter.Next())
        {
          aLockThreadIter.ChangeValue()->Free();
        }
        throw Standard_ProgramError("Error: active ThreadPool is reinitialized");
      }
      aLockThreads.SetValue(aThreadIndex++, &aThread);
    }
  }
  release();

  myShutDown = false;
  if (aNbThreads > 0)
  {
    myThreads.Resize(0, aNbThreads - 1, false);
    int aLastThreadIndex = 0;
    for (NCollection_Array1<EnumeratedThread>::Iterator aThreadIter(myThreads); aThreadIter.More();
         aThreadIter.Next())
    {
      EnumeratedThread& aThread = aThreadIter.ChangeValue();
      aThread.myPool            = this;
      aThread.myThreadIndex     = aLastThreadIndex++;
      aThread.SetFunction(&System::os::OSD_ThreadPool::EnumeratedThread::runThread);
    }
  }
  else
  {
    NCollection_Array1<EnumeratedThread> anEmpty;
    myThreads.Move(anEmpty);
  }
}

System::os::OSD_ThreadPool::~OSD_ThreadPool()
{
  release();
}

void System::os::OSD_ThreadPool::release()
{
  if (myThreads.IsEmpty())
  {
    return;
  }

  myShutDown = true;
  for (NCollection_Array1<EnumeratedThread>::Iterator aThreadIter(myThreads); aThreadIter.More();
       aThreadIter.Next())
  {
    aThreadIter.ChangeValue().WakeUp(nullptr, false);
    aThreadIter.ChangeValue().Wait();
  }
}

void System::os::OSD_ThreadPool::Launcher::perform(JobInterface& theJob)
{
  run(theJob);
  wait();
}

void System::os::OSD_ThreadPool::Launcher::run(JobInterface& theJob)
{
  bool toCatchFpe = System::os::OSD::ToCatchFloatingSignals();
  for (NCollection_Array1<EnumeratedThread*>::Iterator aThreadIter(myThreads);
       aThreadIter.More() && aThreadIter.Value() != nullptr;
       aThreadIter.Next())
  {
    aThreadIter.ChangeValue()->WakeUp(&theJob, toCatchFpe);
  }
}

void System::os::OSD_ThreadPool::Launcher::wait()
{
  int aNbFailures = 0;
  for (NCollection_Array1<EnumeratedThread*>::Iterator aThreadIter(myThreads);
       aThreadIter.More() && aThreadIter.Value() != nullptr;
       aThreadIter.Next())
  {
    aThreadIter.ChangeValue()->WaitIdle();
    if (aThreadIter.Value()->myFailure)
    {
      ++aNbFailures;
    }
  }
  if (aNbFailures == 0)
  {
    return;
  }

  TCollection_AsciiString aFailures;
  for (NCollection_Array1<EnumeratedThread*>::Iterator aThreadIter(myThreads);
       aThreadIter.More() && aThreadIter.Value() != nullptr;
       aThreadIter.Next())
  {
    if (aThreadIter.Value()->myFailure)
    {
      if (aNbFailures == 1)
      {

        throw *aThreadIter.Value()->myFailure;
      }

      if (!aFailures.IsEmpty())
      {
        aFailures += "\n";
      }
      aFailures += aThreadIter.Value()->myFailure->what();
    }
  }

  aFailures = TCollection_AsciiString("Multiple exceptions:\n") + aFailures;
  throw Standard_ProgramError(aFailures.ToCString(), nullptr);
}

void System::os::OSD_ThreadPool::performJob(std::optional<Standard_ProgramError>& theFailure,
                                System::os::OSD_ThreadPool::JobInterface*         theJob,
                                int                                   theThreadIndex)
{
  try
  {
    OCC_CATCH_SIGNALS
    theJob->Perform(theThreadIndex);
  }
  catch (Standard_Failure const& aFailure)
  {
    TCollection_AsciiString aMsg =
      TCollection_AsciiString(aFailure.ExceptionType()) + ": " + aFailure.what();
    theFailure.emplace(aMsg.ToCString(), aFailure.GetStackString());
  }
  catch (std::exception& anStdException)
  {
    TCollection_AsciiString aMsg =
      TCollection_AsciiString(typeid(anStdException).name()) + ": " + anStdException.what();
    theFailure.emplace(aMsg.ToCString(), nullptr);
  }
  catch (...)
  {
    theFailure.emplace("Error: Unknown exception", nullptr);
  }
}

void System::os::OSD_ThreadPool::EnumeratedThread::performThread()
{
  System::os::OSD::SetThreadLocalSignal(System::os::OSD::SignalMode(), false);
  for (;;)
  {
    myWakeEvent.Wait();
    myWakeEvent.Reset();
    if (myPool->myShutDown)
    {
      return;
    }

    myFailure.reset();
    if (myJob != nullptr)
    {
      System::os::OSD::SetThreadLocalSignal(System::os::OSD::SignalMode(), myToCatchFpe);
      System::os::OSD_ThreadPool::performJob(myFailure, myJob, myThreadIndex);
      myJob = nullptr;
    }
    myIdleEvent.Set();
  }
}

void* System::os::OSD_ThreadPool::EnumeratedThread::runThread(void* theTask)
{
  EnumeratedThread* aThread = static_cast<EnumeratedThread*>(theTask);
  aThread->performThread();
  return nullptr;
}

System::os::OSD_ThreadPool::Launcher::Launcher(System::os::OSD_ThreadPool& thePool, int theMaxThreads)
    : mySelfThread(true),
      myNbThreads(0)
{
  const int aNbThreads =
    theMaxThreads > 0 ? std::min(theMaxThreads, thePool.NbThreads())
                      : (theMaxThreads < 0 ? std::max(thePool.NbDefaultThreadsToLaunch(), 1) : 1);
  myThreads.Resize(0, aNbThreads - 1, false);
  myThreads.Init(nullptr);
  if (aNbThreads > 1)
  {
    for (NCollection_Array1<EnumeratedThread>::Iterator aThreadIter(thePool.myThreads);
         aThreadIter.More();
         aThreadIter.Next())
    {
      if (aThreadIter.ChangeValue().Lock())
      {
        myThreads.SetValue(myNbThreads, &aThreadIter.ChangeValue());

        aThreadIter.ChangeValue().myThreadIndex = myNbThreads;
        if (++myNbThreads == aNbThreads - 1)
        {
          break;
        }
      }
    }
  }

  myThreads.SetValue(myNbThreads, &mySelfThread);
  mySelfThread.myThreadIndex = myNbThreads;
  ++myNbThreads;
}

void System::os::OSD_ThreadPool::Launcher::Release()
{
  for (NCollection_Array1<EnumeratedThread*>::Iterator aThreadIter(myThreads);
       aThreadIter.More() && aThreadIter.Value() != nullptr;
       aThreadIter.Next())
  {
    if (aThreadIter.Value() != &mySelfThread)
    {
      aThreadIter.Value()->Free();
    }
  }

  NCollection_Array1<EnumeratedThread*> anEmpty;
  myThreads.Move(anEmpty);
  myNbThreads = 0;
}
