#include <OSD_Parallel.hpp>

#include <OSD_ThreadPool.hpp>

#include <NCollection_Array1.hpp>
#include <OSD_Thread.hpp>

#include <mutex>

namespace
{

  class OSD_Parallel_Threads : public System::os::OSD_ThreadPool, public System::os::OSD_Parallel
  {
  public:
    class Range
    {
    public:
      Range(const System::os::OSD_Parallel::UniversalIterator& theBegin,
            const System::os::OSD_Parallel::UniversalIterator& theEnd)
          : myBegin(theBegin),
            myEnd(theEnd),
            myIt(theBegin)
      {
      }

      inline const System::os::OSD_Parallel::UniversalIterator& Begin() const { return myBegin; }

      inline const System::os::OSD_Parallel::UniversalIterator& End() const { return myEnd; }

      inline System::os::OSD_Parallel::UniversalIterator It() const
      {
        std::lock_guard<std::mutex> aMutex(myMutex);
        return (myIt != myEnd) ? myIt++ : myEnd;
      }

    private:
      Range(const Range& theCopy) = delete;

      Range& operator=(const Range& theCopy) = delete;

    private:
      const System::os::OSD_Parallel::UniversalIterator& myBegin;
      const System::os::OSD_Parallel::UniversalIterator& myEnd;

      mutable System::os::OSD_Parallel::UniversalIterator myIt;
      mutable std::mutex                      myMutex;
    };

    class Task : public JobInterface
    {
    public:
      Task(const System::os::OSD_Parallel::FunctorInterface& thePerformer, Range& theRange)
          : myPerformer(thePerformer),
            myRange(theRange)
      {
      }

      void Perform(int) override
      {
        for (System::os::OSD_Parallel::UniversalIterator anIter = myRange.It(); anIter != myRange.End();
             anIter                                 = myRange.It())
        {
          myPerformer(*anIter);
        }
      }

    private:
      Task(const Task& theCopy) = delete;

      Task& operator=(const Task& theCopy) = delete;

    private:
      const FunctorInterface& myPerformer;
      const Range&            myRange;
    };

    class UniversalLauncher : public Launcher
    {
    public:
      UniversalLauncher(System::os::OSD_ThreadPool& thePool, int theMaxThreads = -1)
          : Launcher(thePool, theMaxThreads)
      {
      }

      void Perform(System::os::OSD_Parallel::UniversalIterator&      theBegin,
                   System::os::OSD_Parallel::UniversalIterator&      theEnd,
                   const System::os::OSD_Parallel::FunctorInterface& theFunctor)
      {
        Range aData(theBegin, theEnd);
        Task  aJob(theFunctor, aData);
        perform(aJob);
      }
    };
  };
} // namespace

void System::os::OSD_Parallel::forEachOcct(UniversalIterator&      theBegin,
                               UniversalIterator&      theEnd,
                               const FunctorInterface& theFunctor,
                               int                     theNbItems)
{
  const occ::handle<System::os::OSD_ThreadPool>& aThreadPool = System::os::OSD_ThreadPool::DefaultPool();
  const int                          aNbThreads =
    theNbItems != -1 ? std::min(theNbItems, aThreadPool->NbDefaultThreadsToLaunch()) : -1;
  OSD_Parallel_Threads::UniversalLauncher aLauncher(*aThreadPool, aNbThreads);
  aLauncher.Perform(theBegin, theEnd, theFunctor);
}

#ifndef HAVE_TBB

void System::os::OSD_Parallel::forEachExternal(UniversalIterator&      theBegin,
                                   UniversalIterator&      theEnd,
                                   const FunctorInterface& theFunctor,
                                   int                     theNbItems)
{
  forEachOcct(theBegin, theEnd, theFunctor, theNbItems);
}

#endif
