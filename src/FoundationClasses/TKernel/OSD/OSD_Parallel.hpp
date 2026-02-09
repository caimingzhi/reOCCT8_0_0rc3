#pragma once

#include <OSD_ThreadPool.hpp>
#include <Standard_Type.hpp>
#include <memory>

class OSD_Parallel
{
private:
  class IteratorInterface
  {
  public:
    virtual ~IteratorInterface() = default;

    virtual bool IsEqual(const IteratorInterface& theOther) const = 0;

    virtual void Increment() = 0;

    virtual IteratorInterface* Clone() const = 0;
  };

  template <class Type>
  class IteratorWrapper : public IteratorInterface
  {
  public:
    IteratorWrapper() = default;

    IteratorWrapper(const Type& theValue)
        : myValue(theValue)
    {
    }

    bool IsEqual(const IteratorInterface& theOther) const override
    {
      return myValue == dynamic_cast<const IteratorWrapper<Type>&>(theOther).myValue;
    }

    void Increment() override { ++myValue; }

    IteratorInterface* Clone() const override { return new IteratorWrapper<Type>(myValue); }

    const Type& Value() const { return myValue; }

  private:
    Type myValue;
  };

protected:
  class UniversalIterator

  {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = IteratorInterface*;
    using difference_type   = ptrdiff_t;
    using pointer           = value_type;
    using reference         = value_type;

    UniversalIterator() = default;

    UniversalIterator(IteratorInterface* theOther)
        : myPtr(theOther)
    {
    }

    UniversalIterator(const UniversalIterator& theOther)
        : myPtr(theOther.myPtr->Clone())
    {
    }

    UniversalIterator& operator=(const UniversalIterator& theOther)
    {
      myPtr.reset(theOther.myPtr->Clone());
      return *this;
    }

    bool operator!=(const UniversalIterator& theOther) const
    {
      return !myPtr->IsEqual(*theOther.myPtr);
    }

    bool operator==(const UniversalIterator& theOther) const
    {
      return myPtr->IsEqual(*theOther.myPtr);
    }

    UniversalIterator& operator++()
    {
      myPtr->Increment();
      return *this;
    }

    UniversalIterator operator++(int)
    {
      UniversalIterator aValue(*this);
      myPtr->Increment();
      return aValue;
    }

    reference operator*() const { return myPtr.get(); }

    reference operator*() { return myPtr.get(); }

  private:
    std::unique_ptr<IteratorInterface> myPtr;
  };

  class FunctorInterface
  {
  public:
    virtual ~FunctorInterface() = default;

    virtual void operator()(IteratorInterface* theIterator) const = 0;

    template <typename Iterator>
    static const Iterator& DownCast(IteratorInterface* theIterator)
    {
      return dynamic_cast<OSD_Parallel::IteratorWrapper<Iterator>*>(theIterator)->Value();
    }
  };

private:
  template <class Iterator, class Functor>
  class FunctorWrapperIter : public FunctorInterface
  {
  public:
    FunctorWrapperIter(const Functor& theFunctor)
        : myFunctor(theFunctor)
    {
    }

    void operator()(IteratorInterface* theIterator) const override
    {
      const Iterator& anIt = DownCast<Iterator>(theIterator);
      myFunctor(*anIt);
    }

  private:
    FunctorWrapperIter(const FunctorWrapperIter&)       = delete;
    void           operator=(const FunctorWrapperIter&) = delete;
    const Functor& myFunctor;
  };

  template <class Functor>
  class FunctorWrapperInt : public FunctorInterface
  {
  public:
    FunctorWrapperInt(const Functor& theFunctor)
        : myFunctor(theFunctor)
    {
    }

    void operator()(IteratorInterface* theIterator) const override
    {
      int anIndex = DownCast<int>(theIterator);
      myFunctor(anIndex);
    }

  private:
    FunctorWrapperInt(const FunctorWrapperInt&)        = delete;
    void           operator=(const FunctorWrapperInt&) = delete;
    const Functor& myFunctor;
  };

  template <class Functor>
  class FunctorWrapperForThreadPool
  {
  public:
    FunctorWrapperForThreadPool(const Functor& theFunctor)
        : myFunctor(theFunctor)
    {
    }

    void operator()(int theThreadIndex, int theElemIndex) const
    {
      (void)theThreadIndex;
      myFunctor(theElemIndex);
    }

  private:
    FunctorWrapperForThreadPool(const FunctorWrapperForThreadPool&) = delete;
    void           operator=(const FunctorWrapperForThreadPool&)    = delete;
    const Functor& myFunctor;
  };

private:
  Standard_EXPORT static void forEachOcct(UniversalIterator&      theBegin,
                                          UniversalIterator&      theEnd,
                                          const FunctorInterface& theFunctor,
                                          int                     theNbItems);

  Standard_EXPORT static void forEachExternal(UniversalIterator&      theBegin,
                                              UniversalIterator&      theEnd,
                                              const FunctorInterface& theFunctor,
                                              int                     theNbItems);

public:
  Standard_EXPORT static bool ToUseOcctThreads();

  Standard_EXPORT static void SetUseOcctThreads(bool theToUseOcct);

  Standard_EXPORT static int NbLogicalProcessors();

  template <typename InputIterator, typename Functor>
  static void ForEach(InputIterator  theBegin,
                      InputIterator  theEnd,
                      const Functor& theFunctor,
                      const bool     isForceSingleThreadExecution = false,
                      int            theNbItems                   = -1)
  {
    if (isForceSingleThreadExecution || theNbItems == 1)
    {
      for (InputIterator it(theBegin); it != theEnd; ++it)
        theFunctor(*it);
    }
    else
    {
      UniversalIterator aBegin(new IteratorWrapper<InputIterator>(theBegin));
      UniversalIterator aEnd(new IteratorWrapper<InputIterator>(theEnd));
      FunctorWrapperIter<InputIterator, Functor> aFunctor(theFunctor);
      if (ToUseOcctThreads())
      {
        forEachOcct(aBegin, aEnd, aFunctor, theNbItems);
      }
      else
      {
        forEachExternal(aBegin, aEnd, aFunctor, theNbItems);
      }
    }
  }

  template <typename Functor>
  static void For(const int      theBegin,
                  const int      theEnd,
                  const Functor& theFunctor,
                  const bool     isForceSingleThreadExecution = false)
  {
    const int aRange = theEnd - theBegin;
    if (isForceSingleThreadExecution || aRange == 1)
    {
      for (int it(theBegin); it != theEnd; ++it)
        theFunctor(it);
    }
    else if (ToUseOcctThreads())
    {
      const occ::handle<OSD_ThreadPool>&   aThreadPool = OSD_ThreadPool::DefaultPool();
      OSD_ThreadPool::Launcher             aPoolLauncher(*aThreadPool, aRange);
      FunctorWrapperForThreadPool<Functor> aFunctor(theFunctor);
      aPoolLauncher.Perform(theBegin, theEnd, aFunctor);
    }
    else
    {
      UniversalIterator          aBegin(new IteratorWrapper<int>(theBegin));
      UniversalIterator          aEnd(new IteratorWrapper<int>(theEnd));
      FunctorWrapperInt<Functor> aFunctor(theFunctor);
      forEachExternal(aBegin, aEnd, aFunctor, aRange);
    }
  }
};
