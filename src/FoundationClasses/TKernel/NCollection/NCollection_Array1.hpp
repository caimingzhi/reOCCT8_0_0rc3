#pragma once

#include <Standard_DimensionMismatch.hpp>
#include <Standard_OutOfMemory.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_OutOfRange.hpp>

#include <NCollection_DefineAlloc.hpp>
#include <NCollection_Iterator.hpp>
#include <NCollection_Allocator.hpp>
#include <StdFail_NotDone.hpp>
#include <NCollection_IndexedIterator.hpp>

#include <algorithm>

template <class TheItemType>
class NCollection_Array1
{
public:
  DEFINE_STANDARD_ALLOC;
  DEFINE_NCOLLECTION_ALLOC;

public:
  typedef NCollection_Allocator<TheItemType> allocator_type;

public:
  using value_type      = TheItemType;
  using size_type       = size_t;
  using difference_type = size_t;
  using pointer         = TheItemType*;
  using const_pointer   = const TheItemType*;
  using reference       = TheItemType&;
  using const_reference = const TheItemType&;

  using iterator       = NCollection_IndexedIterator<std::random_access_iterator_tag,
                                                     NCollection_Array1,
                                                     value_type,
                                                     false>;
  using const_iterator = NCollection_IndexedIterator<std::random_access_iterator_tag,
                                                     NCollection_Array1,
                                                     value_type,
                                                     true>;
  using Iterator       = NCollection_Iterator<NCollection_Array1<TheItemType>>;

public:
  const_iterator begin() const noexcept { return const_iterator(*this); }

  iterator begin() noexcept { return iterator(*this); }

  const_iterator cbegin() const noexcept { return const_iterator(*this); }

  iterator end() noexcept { return iterator(mySize, *this); }

  const_iterator end() const noexcept { return const_iterator(mySize, *this); }

  const_iterator cend() const noexcept { return const_iterator(mySize, *this); }

public:
  NCollection_Array1() noexcept
      : myLowerBound(1),
        mySize(0)
  {
  }

  explicit NCollection_Array1(const int theLower, const int theUpper)
      : myLowerBound(theLower),
        mySize(theUpper - theLower + 1)
  {
    if (mySize == 0)
    {
      return;
    }
    myPointer = myAllocator.allocate(mySize);
    myIsOwner = true;
    construct(0, mySize);
  }

  explicit NCollection_Array1(const allocator_type& theAlloc,
                              const int             theLower,
                              const int             theUpper)
      : myLowerBound(theLower),
        mySize(theUpper - theLower + 1),
        myPointer(nullptr),
        myIsOwner(false),
        myAllocator(theAlloc)
  {
    if (mySize == 0)
    {
      return;
    }
    myPointer = myAllocator.allocate(mySize);
    myIsOwner = true;
    construct(0, mySize);
  }

  explicit NCollection_Array1(const_reference theBegin,
                              const int       theLower,
                              const int       theUpper,
                              const bool      theUseBuffer = true)
      : myLowerBound(theLower),
        mySize(theUpper - theLower + 1),
        myPointer(theUseBuffer ? const_cast<pointer>(&theBegin) : nullptr),
        myIsOwner(!theUseBuffer)
  {
    if (!myIsOwner)
    {
      return;
    }
    myPointer = myAllocator.allocate(mySize);
    myIsOwner = true;
    construct(0, mySize);
  }

  NCollection_Array1(const NCollection_Array1& theOther)
      : myLowerBound(theOther.myLowerBound),
        mySize(theOther.mySize)
  {
    if (mySize == 0)
    {
      return;
    }
    myPointer = myAllocator.allocate(mySize);
    myIsOwner = true;
    copyConstruct(theOther.myPointer, mySize);
  }

  NCollection_Array1(NCollection_Array1&& theOther) noexcept
      : myLowerBound(theOther.myLowerBound),
        mySize(theOther.mySize),
        myPointer(theOther.myPointer),
        myIsOwner(theOther.myIsOwner)
  {
    theOther.myIsOwner    = false;
    theOther.myPointer    = nullptr;
    theOther.mySize       = 0;
    theOther.myLowerBound = 1;
  }

  virtual ~NCollection_Array1()
  {
    if (!myIsOwner)
    {
      return;
    }
    destroy(myPointer, 0, mySize);
    myAllocator.deallocate(myPointer, mySize);
  }

  void Init(const_reference theValue)
  {
    for (size_t anIter = 0; anIter < mySize; anIter++)
    {
      myPointer[anIter] = theValue;
    }
  }

  int Size() const noexcept { return Length(); }

  int Length() const noexcept { return static_cast<int>(mySize); }

  bool IsEmpty() const noexcept { return mySize == 0; }

  int Lower() const noexcept { return myLowerBound; }

  int Upper() const noexcept { return myLowerBound + static_cast<int>(mySize) - 1; }

  NCollection_Array1& Assign(const NCollection_Array1& theOther)
  {
    if (&theOther == this)
    {
      return *this;
    }
    Standard_DimensionMismatch_Raise_if(mySize != theOther.mySize, "NCollection_Array1::operator=");
    for (size_t anInd = 0; anInd < mySize; anInd++)
    {
      myPointer[anInd] = theOther.myPointer[anInd];
    }

    return *this;
  }

  NCollection_Array1& Move(NCollection_Array1&& theOther) noexcept
  {
    if (&theOther == this)
    {
      return *this;
    }
    if (myIsOwner)
    {
      destroy(myPointer, 0, mySize);
      myAllocator.deallocate(myPointer, mySize);
    }
    myLowerBound          = theOther.myLowerBound;
    mySize                = theOther.mySize;
    myPointer             = theOther.myPointer;
    myIsOwner             = theOther.myIsOwner;
    theOther.myIsOwner    = false;
    theOther.myPointer    = nullptr;
    theOther.mySize       = 0;
    theOther.myLowerBound = 1;
    return *this;
  }

  NCollection_Array1& Move(NCollection_Array1& theOther) noexcept
  {
    return Move(std::move(theOther));
  }

  NCollection_Array1& operator=(const NCollection_Array1& theOther) { return Assign(theOther); }

  NCollection_Array1& operator=(NCollection_Array1&& theOther) noexcept
  {
    return Move(std::forward<NCollection_Array1>(theOther));
  }

  const_reference First() const noexcept { return myPointer[0]; }

  reference ChangeFirst() noexcept { return myPointer[0]; }

  const_reference Last() const noexcept { return myPointer[mySize - 1]; }

  reference ChangeLast() noexcept { return myPointer[mySize - 1]; }

  const_reference Value(const int theIndex) const
  {
    const size_t aPos = theIndex - myLowerBound;
    Standard_OutOfRange_Raise_if(aPos >= mySize, "NCollection_Array1::Value");
    return myPointer[aPos];
  }

  const_reference operator()(const int theIndex) const { return Value(theIndex); }

  const_reference operator[](const int theIndex) const { return Value(theIndex); }

  reference ChangeValue(const int theIndex)
  {
    const size_t aPos = theIndex - myLowerBound;
    Standard_OutOfRange_Raise_if(aPos >= mySize, "NCollection_Array1::ChangeValue");
    return myPointer[aPos];
  }

  reference operator()(const int theIndex) { return ChangeValue(theIndex); }

  reference operator[](const int theIndex) { return ChangeValue(theIndex); }

  void SetValue(const int theIndex, const value_type& theItem)
  {
    const size_t aPos = theIndex - myLowerBound;
    Standard_OutOfRange_Raise_if(aPos >= mySize, "NCollection_Array1::SetValue");
    myPointer[aPos] = theItem;
  }

  void SetValue(const int theIndex, value_type&& theItem)
  {
    const size_t aPos = theIndex - myLowerBound;
    Standard_OutOfRange_Raise_if(aPos >= mySize, "NCollection_Array1::SetValue");
    myPointer[aPos] = std::forward<value_type>(theItem);
  }

  void UpdateLowerBound(const int theLower) noexcept { myLowerBound = theLower; }

  void UpdateUpperBound(const int theUpper) noexcept
  {
    myLowerBound = myLowerBound - Upper() + theUpper;
  }

  void Resize(const int theLower, const int theUpper, const bool theToCopyData)
  {
    Standard_RangeError_Raise_if(theUpper < theLower, "NCollection_Array1::Resize");
    const size_t aNewSize     = static_cast<size_t>(theUpper - theLower + 1);
    pointer      aPrevContPnt = myPointer;
    if (aNewSize == mySize)
    {
      myLowerBound = theLower;
      return;
    }
    if (myIsOwner)
    {
      if (theToCopyData)
        destroy(myPointer, aNewSize, mySize);
      else
        destroy(myPointer, 0, mySize);
    }
    myLowerBound = theLower;
    if (theToCopyData)
    {
      const size_t aMinSize = (std::min)(aNewSize, mySize);
      if (myIsOwner)
      {
        myPointer = myAllocator.reallocate(myPointer, aNewSize);
      }
      else
      {
        myPointer = myAllocator.allocate(aNewSize);
        copyConstruct(aPrevContPnt, aMinSize);
      }
      construct(mySize, aNewSize);
    }
    else
    {
      if (myIsOwner)
        myAllocator.deallocate(aPrevContPnt, mySize);
      myPointer = myAllocator.allocate(aNewSize);
      construct(0, aNewSize);
    }
    mySize    = aNewSize;
    myIsOwner = true;
  }

  bool IsDeletable() const noexcept { return myIsOwner; }

  friend iterator;
  friend const_iterator;

protected:
  const_reference at(const size_t theIndex) const
  {
    Standard_OutOfRange_Raise_if(theIndex >= mySize, "NCollection_Array1::at");
    return myPointer[theIndex];
  }

  reference at(const size_t theIndex)
  {
    Standard_OutOfRange_Raise_if(theIndex >= mySize, "NCollection_Array1::at");
    return myPointer[theIndex];
  }

protected:
  template <typename U = TheItemType>
  typename std::enable_if<std::is_trivially_default_constructible<U>::value, void>::type construct(
    const size_t,
    const size_t)
  {
  }

  template <typename U = TheItemType>
  typename std::enable_if<!std::is_trivially_default_constructible<U>::value, void>::type construct(
    const size_t theFrom,
    const size_t theTo)
  {
    for (size_t anInd = theFrom; anInd < theTo; anInd++)
    {
      myAllocator.construct(myPointer + anInd);
    }
  }

  template <typename U = TheItemType>
  typename std::enable_if<std::is_trivially_destructible<U>::value, void>::type destroy(
    pointer,
    const size_t,
    const size_t)
  {
  }

  template <typename U = TheItemType>
  typename std::enable_if<!std::is_trivially_destructible<U>::value, void>::type destroy(
    pointer      theWhat,
    const size_t theFrom,
    const size_t theTo)
  {
    for (size_t anInd = theFrom; anInd < theTo; anInd++)
    {
      myAllocator.destroy(theWhat + anInd);
    }
  }

  void copyConstruct(const pointer theFrom, const size_t theCount)
  {
    for (size_t anInd = 0; anInd < theCount; anInd++)
    {
      myAllocator.construct(myPointer + anInd, theFrom[anInd]);
    }
  }

  int            myLowerBound;
  size_t         mySize;
  pointer        myPointer = nullptr;
  bool           myIsOwner = false;
  allocator_type myAllocator;
};
