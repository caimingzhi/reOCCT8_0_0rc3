#pragma once

#include <OSD_Parallel.hpp>
#include <OSD_ThreadPool.hpp>
#include <NCollection_DataMap.hpp>
#include <OSD_Thread.hpp>

#include <mutex>

class BOPTools_Parallel
{
  template <class TypeSolverVector>
  class Functor
  {
  public:
    explicit Functor(TypeSolverVector& theSolverVec)
        : mySolvers(theSolverVec)
    {
    }

    void operator()(const int theIndex) const
    {
      typename TypeSolverVector::value_type& aSolver = mySolvers[theIndex];
      aSolver.Perform();
    }

  private:
    Functor(const Functor&)            = delete;
    Functor& operator=(const Functor&) = delete;

  private:
    TypeSolverVector& mySolvers;
  };

  template <class TypeSolverVector, class TypeContext>
  class ContextFunctor
  {
  public:
    explicit ContextFunctor(TypeSolverVector& theVector)
        : mySolverVector(theVector)
    {
    }

    void SetContext(const opencascade::handle<TypeContext>& theContext)
    {
      myContextMap.Bind(OSD_Thread::Current(), theContext);
    }

    const opencascade::handle<TypeContext>& GetThreadContext() const
    {
      const Standard_ThreadId aThreadID = OSD_Thread::Current();
      if (const opencascade::handle<TypeContext>* aContextPtr = myContextMap.Seek(aThreadID))
      {
        if (!aContextPtr->IsNull())
        {
          return *aContextPtr;
        }
      }

      opencascade::handle<TypeContext> aContext =
        new TypeContext(NCollection_BaseAllocator::CommonBaseAllocator());

      std::lock_guard<std::mutex> aLock(myMutex);
      myContextMap.Bind(aThreadID, aContext);
      return myContextMap(aThreadID);
    }

    void operator()(const int theIndex) const
    {
      const opencascade::handle<TypeContext>& aContext = GetThreadContext();
      typename TypeSolverVector::value_type&  aSolver  = mySolverVector[theIndex];

      aSolver.SetContext(aContext);
      aSolver.Perform();
    }

  private:
    ContextFunctor(const ContextFunctor&)            = delete;
    ContextFunctor& operator=(const ContextFunctor&) = delete;

  private:
    TypeSolverVector&                                                                mySolverVector;
    mutable NCollection_DataMap<Standard_ThreadId, opencascade::handle<TypeContext>> myContextMap;
    mutable std::mutex                                                               myMutex;
  };

  template <class TypeSolverVector, class TypeContext>
  class ContextFunctor2
  {
  public:
    explicit ContextFunctor2(TypeSolverVector&               theVector,
                             const OSD_ThreadPool::Launcher& thePoolLauncher)
        : mySolverVector(theVector),
          myContextArray(thePoolLauncher.LowerThreadIndex(), thePoolLauncher.UpperThreadIndex())
    {
    }

    void SetContext(const opencascade::handle<TypeContext>& theContext)
    {

      myContextArray.ChangeLast() = theContext;
    }

    void operator()(int theThreadIndex, int theIndex) const
    {
      opencascade::handle<TypeContext>& aContext = myContextArray.ChangeValue(theThreadIndex);
      if (aContext.IsNull())
      {
        aContext = new TypeContext(NCollection_BaseAllocator::CommonBaseAllocator());
      }
      typename TypeSolverVector::value_type& aSolver = mySolverVector[theIndex];
      aSolver.SetContext(aContext);
      aSolver.Perform();
    }

  private:
    ContextFunctor2(const ContextFunctor2&)            = delete;
    ContextFunctor2& operator=(const ContextFunctor2&) = delete;

  private:
    TypeSolverVector&                                            mySolverVector;
    mutable NCollection_Array1<opencascade::handle<TypeContext>> myContextArray;
  };

public:
  template <class TypeSolverVector>
  static void Perform(bool theIsRunParallel, TypeSolverVector& theSolverVector)
  {
    Functor<TypeSolverVector> aFunctor(theSolverVector);
    OSD_Parallel::For(0, theSolverVector.Length(), aFunctor, !theIsRunParallel);
  }

  template <class TypeSolverVector, class TypeContext>
  static void Perform(bool                              theIsRunParallel,
                      TypeSolverVector&                 theSolverVector,
                      opencascade::handle<TypeContext>& theContext)
  {
    if (OSD_Parallel::ToUseOcctThreads())
    {
      const occ::handle<OSD_ThreadPool>&             aThreadPool = OSD_ThreadPool::DefaultPool();
      OSD_ThreadPool::Launcher                       aPoolLauncher(*aThreadPool,
                                             theIsRunParallel ? theSolverVector.Length() : 0);
      ContextFunctor2<TypeSolverVector, TypeContext> aFunctor(theSolverVector, aPoolLauncher);
      aFunctor.SetContext(theContext);
      aPoolLauncher.Perform(0, theSolverVector.Length(), aFunctor);
    }
    else
    {
      ContextFunctor<TypeSolverVector, TypeContext> aFunctor(theSolverVector);
      aFunctor.SetContext(theContext);
      OSD_Parallel::For(0, theSolverVector.Length(), aFunctor, !theIsRunParallel);
    }
  }
};
