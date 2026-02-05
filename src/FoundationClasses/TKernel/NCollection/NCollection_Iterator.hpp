#pragma once

#include <Standard_Assert.hpp>
#include <iterator>

//! Helper class that allows to use NCollection iterators as STL iterators.
//! NCollection iterator can be extended to STL iterator of any category by
//! adding necessary methods: STL forward iterator requires IsEqual method,
//! STL bidirectional iterator requires Previous method, and STL random access
//! iterator requires Offset and Differ methods. See NCollection_Vector as
//! example of declaring custom STL iterators.
template <class Container>
class NCollection_Iterator
{
public:
  NCollection_Iterator()
      : myCur(typename Container::iterator()),
        myLast(typename Container::iterator())
  {
  }

  NCollection_Iterator(const NCollection_Iterator& theOther)
      : myCur(theOther.myCur),
        myLast(theOther.myLast)
  {
  }

  NCollection_Iterator(const Container& theList)
      : myCur(const_cast<Container&>(theList).begin()),
        myLast(const_cast<Container&>(theList).end())
  {
  }

  NCollection_Iterator(const Container& theList, const typename Container::iterator& theOther)
      : myCur(theOther),
        myLast(const_cast<Container&>(theList).end())
  {
  }

  NCollection_Iterator(const Container& theList, typename Container::iterator&& theOther)
      : myCur(theOther),
        myLast(const_cast<Container&>(theList).end())
  {
  }

  ~NCollection_Iterator() noexcept = default;

  void Init(Container& theList)
  {
    myCur  = theList.begin();
    myLast = theList.end();
  }

  void Init(const Container& theList) { Init(const_cast<Container&>(theList)); }

  virtual bool More() const noexcept { return myCur != myLast; }

  void Initialize(Container& theList) { Init(theList); }

  void Initialize(const Container& theList) { Init(theList); }

  const typename Container::iterator& ValueIter() const noexcept { return myCur; }

  typename Container::iterator& ChangeValueIter() noexcept { return myCur; }

  const typename Container::iterator& EndIter() const noexcept { return myLast; }

  typename Container::iterator& ChangeEndIter() noexcept { return myLast; }

  virtual void Next() noexcept { ++(myCur); }

  const typename Container::const_reference Value() const { return *myCur; }

  const typename Container::reference ChangeValue() { return *myCur; }

  bool operator==(const NCollection_Iterator& theOther) noexcept
  {
    return myLast == theOther.myLast && myCur == theOther.myCur;
  }

  bool operator!=(const NCollection_Iterator& theOther) noexcept
  {
    return myLast != theOther.myLast || myCur != theOther.myCur;
  }

  NCollection_Iterator& operator=(const NCollection_Iterator& theOther) noexcept
  {
    if (this != &theOther)
    {
      myLast = theOther.myLast;
      myCur  = theOther.myCur;
    }
    return *this;
  }

  NCollection_Iterator& operator=(NCollection_Iterator&& theOther) noexcept
  {
    if (this != &theOther)
    {
      myLast = std::move(theOther.myLast);
      myCur  = std::move(theOther.myCur);
    }
    return *this;
  }

private:
  typename Container::iterator myCur;
  typename Container::iterator myLast;
};
