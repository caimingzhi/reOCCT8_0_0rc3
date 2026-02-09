#pragma once

#include <NCollection_Allocator.hpp>
#include <NCollection_BasePointerVector.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_OutOfMemory.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_OutOfRange.hpp>

#include <NCollection_DefineAlloc.hpp>
#include <NCollection_Iterator.hpp>
#include <NCollection_OccAllocator.hpp>
#include <StdFail_NotDone.hpp>
#include <NCollection_IndexedIterator.hpp>

#include <locale>
#include <vector>

template <class TheItemType>
class NCollection_DynamicArray
{
public:
  DEFINE_STANDARD_ALLOC;
  DEFINE_NCOLLECTION_ALLOC;

public:
  typedef NCollection_OccAllocator<TheItemType> allocator_type;
  typedef NCollection_BasePointerVector         vector;

public:
  using value_type      = TheItemType;
  using size_type       = size_t;
  using difference_type = size_t;
  using pointer         = TheItemType*;
  using const_pointer   = TheItemType&;
  using reference       = TheItemType&;
  using const_reference = const TheItemType&;

public:
  using iterator       = NCollection_IndexedIterator<std::random_access_iterator_tag,
                                                     NCollection_DynamicArray,
                                                     value_type,
                                                     false>;
  using const_iterator = NCollection_IndexedIterator<std::random_access_iterator_tag,
                                                     NCollection_DynamicArray,
                                                     value_type,
                                                     true>;
  using Iterator       = NCollection_Iterator<NCollection_DynamicArray<TheItemType>>;

public:
  const_iterator begin() const noexcept { return const_iterator(*this); }

  iterator begin() noexcept { return iterator(*this); }

  const_iterator cbegin() const noexcept { return const_iterator(*this); }

  iterator end() noexcept { return iterator(myUsedSize, *this); }

  const_iterator end() const noexcept { return const_iterator(myUsedSize, *this); }

  const_iterator cend() const noexcept { return const_iterator(myUsedSize, *this); }

public:
  NCollection_DynamicArray(const int theIncrement = 256)
      : myAlloc(),
        myInternalSize(theIncrement),
        myUsedSize(0)
  {
  }

  explicit NCollection_DynamicArray(const int                                     theIncrement,
                                    const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : myAlloc(allocator_type(theAllocator)),
        myInternalSize(theIncrement),
        myUsedSize(0)
  {
  }

  explicit NCollection_DynamicArray(const int theIncrement, const allocator_type& theAllocator)
      : myAlloc(theAllocator),
        myInternalSize(theIncrement),
        myUsedSize(0)
  {
  }

  NCollection_DynamicArray(const NCollection_DynamicArray& theOther)
      : myContainer(theOther.myContainer),
        myAlloc(theOther.myAlloc),
        myInternalSize(theOther.myInternalSize),
        myUsedSize(theOther.myUsedSize)
  {
    copyDate();
  }

  NCollection_DynamicArray(NCollection_DynamicArray&& theOther) noexcept
      : myContainer(std::move(theOther.myContainer)),
        myAlloc(theOther.myAlloc),
        myInternalSize(theOther.myInternalSize),
        myUsedSize(theOther.myUsedSize)
  {
    theOther.myUsedSize = 0;
  }

  ~NCollection_DynamicArray() { Clear(true); }

  int Length() const noexcept { return static_cast<int>(myUsedSize); }

  int Size() const noexcept { return Length(); }

  int Lower() const noexcept { return 0; }

  int Upper() const noexcept { return Length() - 1; }

  bool IsEmpty() const noexcept { return myUsedSize == 0; }

  NCollection_DynamicArray& Assign(const NCollection_DynamicArray& theOther,
                                   const bool                      theOwnAllocator = true)
  {
    if (&theOther == this)
    {
      return *this;
    }
    if (!theOwnAllocator)
    {
      Clear(myAlloc != theOther.myAlloc);
      myAlloc = theOther.myAlloc;
    }
    else
    {
      Clear(false);
    }
    myContainer    = theOther.myContainer;
    myInternalSize = theOther.myInternalSize;
    myUsedSize     = theOther.myUsedSize;
    copyDate();
    return *this;
  }

  NCollection_DynamicArray& Assign(NCollection_DynamicArray&& theOther)
  {
    if (&theOther == this)
    {
      return *this;
    }
    Clear(true);
    myContainer         = std::move(theOther.myContainer);
    myAlloc             = theOther.myAlloc;
    myInternalSize      = theOther.myInternalSize;
    myUsedSize          = theOther.myUsedSize;
    theOther.myUsedSize = 0;
    return *this;
  }

  NCollection_DynamicArray& operator=(const NCollection_DynamicArray& theOther)
  {
    return Assign(theOther, false);
  }

  NCollection_DynamicArray& operator=(NCollection_DynamicArray&& theOther) noexcept
  {
    return Assign(std::forward<NCollection_DynamicArray>(theOther));
  }

  reference Append(const TheItemType& theValue)
  {
    if (myUsedSize >= availableSize())
    {
      expandArray();
    }
    pointer aPnt = &at(myUsedSize++);
    myAlloc.construct(aPnt, theValue);
    return *aPnt;
  }

  reference Append(TheItemType&& theValue)
  {
    if (myUsedSize >= availableSize())
    {
      expandArray();
    }
    pointer aPnt = &at(myUsedSize++);
    myAlloc.construct(aPnt, std::forward<TheItemType>(theValue));
    return *aPnt;
  }

  void EraseLast()
  {
    if (myUsedSize == 0)
    {
      return;
    }
    TheItemType* aLastElem = &ChangeLast();
    myAlloc.destroy(aLastElem);
    myUsedSize--;
  }

  reference Appended()
  {
    if (myUsedSize >= availableSize())
    {
      expandArray();
    }
    pointer aPnt = &at(myUsedSize++);
    myAlloc.construct(aPnt);
    return *aPnt;
  }

  const_reference operator()(const int theIndex) const noexcept { return Value(theIndex); }

  const_reference operator[](const int theIndex) const noexcept { return Value(theIndex); }

  const_reference operator[](const size_t theIndex) const noexcept { return at(theIndex); }

  const_reference Value(const int theIndex) const noexcept
  {
    return at(static_cast<int>(theIndex));
  }

  const_reference First() const noexcept { return getArray()[0][0]; }

  reference ChangeFirst() noexcept { return getArray()[0][0]; }

  const_reference Last() const noexcept { return at(myUsedSize - 1); }

  reference ChangeLast() noexcept { return at(myUsedSize - 1); }

  reference operator()(const int theIndex) noexcept { return ChangeValue(theIndex); }

  reference operator[](const int theIndex) noexcept { return ChangeValue(theIndex); }

  reference operator[](const size_t theIndex) noexcept { return at(theIndex); }

  reference ChangeValue(const int theIndex) noexcept { return at(static_cast<int>(theIndex)); }

  reference SetValue(const int theIndex, const TheItemType& theValue)
  {
    const size_t aBlockInd = static_cast<size_t>(theIndex / myInternalSize);
    const size_t anIndex   = static_cast<size_t>(theIndex);
    for (size_t aInd = myContainer.Size(); aInd <= aBlockInd; aInd++)
    {
      expandArray();
    }
    if (myUsedSize <= anIndex)
    {
      for (; myUsedSize < anIndex; myUsedSize++)
      {
        pointer aPnt = &at(myUsedSize);
        myAlloc.construct(aPnt);
      }
      myUsedSize++;
    }
    pointer aPnt = &at(anIndex);
    myAlloc.construct(aPnt, theValue);
    return *aPnt;
  }

  reference SetValue(const int theIndex, TheItemType&& theValue)
  {
    const size_t aBlockInd = static_cast<size_t>(theIndex / myInternalSize);
    const size_t anIndex   = static_cast<size_t>(theIndex);
    for (size_t aInd = myContainer.Size(); aInd <= aBlockInd; aInd++)
    {
      expandArray();
    }
    if (myUsedSize <= anIndex)
    {
      for (; myUsedSize < anIndex; myUsedSize++)
      {
        pointer aPnt = &at(myUsedSize);
        myAlloc.construct(aPnt);
      }
      myUsedSize++;
    }
    pointer aPnt = &at(anIndex);
    myAlloc.construct(aPnt, std::forward<TheItemType>(theValue));
    return *aPnt;
  }

  void Clear(const bool theReleaseMemory = false)
  {
    size_t aUsedSize = 0;
    for (size_t aBlockInd = 0; aBlockInd < myContainer.Size(); aBlockInd++)
    {
      TheItemType* aCurStart = getArray()[aBlockInd];
      for (size_t anElemInd = 0; anElemInd < myInternalSize && aUsedSize < myUsedSize;
           anElemInd++, aUsedSize++)
      {
        aCurStart[anElemInd].~TheItemType();
      }
      if (theReleaseMemory)
        myAlloc.deallocate(aCurStart, myInternalSize);
    }
    if (theReleaseMemory)
      myContainer.Clear(theReleaseMemory);
    myUsedSize = 0;
  }

  void SetIncrement(const int theIncrement) noexcept
  {
    if (myUsedSize != 0)
    {
      return;
    }
    myInternalSize = static_cast<size_t>(theIncrement);
  }

  friend iterator;
  friend const_iterator;

protected:
  size_t availableSize() const noexcept { return myContainer.Size() * myInternalSize; }

  TheItemType* expandArray()
  {
    TheItemType* aNewBlock = myAlloc.allocate(myInternalSize);
    myContainer.Append(aNewBlock);
    return aNewBlock;
  }

  reference at(const size_t theInd) noexcept
  {
    return getArray()[theInd / myInternalSize][theInd % myInternalSize];
  }

  const_reference at(const size_t theInd) const noexcept
  {
    return getArray()[theInd / myInternalSize][theInd % myInternalSize];
  }

  void copyDate()
  {
    size_t aUsedSize = 0;
    for (size_t aBlockInd = 0; aBlockInd < myContainer.Size(); aBlockInd++)
    {
      TheItemType* aCurStart = getArray()[aBlockInd];
      TheItemType* aNewBlock = myAlloc.allocate(myInternalSize);
      for (size_t anElemInd = 0; anElemInd < myInternalSize && aUsedSize < myUsedSize;
           anElemInd++, aUsedSize++)
      {
        pointer aPnt = &aNewBlock[anElemInd];
        myAlloc.construct(aPnt, aCurStart[anElemInd]);
      }
      getArray()[aBlockInd] = aNewBlock;
    }
  }

  TheItemType** getArray() const noexcept { return (TheItemType**)myContainer.GetArray(); }

protected:
  vector         myContainer;
  allocator_type myAlloc;
  size_t         myInternalSize;
  size_t         myUsedSize;
};

template <class TheItemType>
using NCollection_Vector = NCollection_DynamicArray<TheItemType>;
