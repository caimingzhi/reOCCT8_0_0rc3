#ifdef HAVE_TBB

  #include <OSD_Parallel.hpp>
  #include <OSD_ThreadPool.hpp>
  #include <Standard_ProgramError.hpp>

Standard_DISABLE_DEPRECATION_WARNINGS
  #include <tbb/parallel_for.h>
  #include <tbb/parallel_for_each.h>
  #include <tbb/blocked_range.h>
  #if TBB_VERSION_MAJOR < 2021
    #include <tbb/task_scheduler_init.h>
  #endif
  Standard_ENABLE_DEPRECATION_WARNINGS

  void
  OSD_Parallel::forEachExternal(UniversalIterator&      theBegin,
                                UniversalIterator&      theEnd,
                                const FunctorInterface& theFunctor,
                                int                     theNbItems)
{
  #if TBB_VERSION_MAJOR >= 2021

  (void)theNbItems;
  tbb::parallel_for_each(theBegin, theEnd, theFunctor);
  #else
  try
  {
    const occ::handle<OSD_ThreadPool>& aThreadPool = OSD_ThreadPool::DefaultPool();
    const int aNbThreads = theNbItems > 0 ? aThreadPool->NbDefaultThreadsToLaunch() : -1;
    tbb::task_scheduler_init aScheduler(aNbThreads);
    tbb::parallel_for_each(theBegin, theEnd, theFunctor);
  }
  catch (tbb::captured_exception& anException)
  {
    throw Standard_ProgramError(anException.what());
  }
  #endif
}

#endif
