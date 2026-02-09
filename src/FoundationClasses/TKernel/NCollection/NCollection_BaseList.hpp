#pragma once

#include <Standard_NoSuchObject.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <NCollection_ListNode.hpp>

typedef void (*NCollection_DelListNode)(NCollection_ListNode*,
                                        occ::handle<NCollection_BaseAllocator>& theAl);

class NCollection_BaseList
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

public:
  class Iterator
  {
  public:
    Iterator() noexcept
        : myCurrent(nullptr),
          myPrevious(nullptr)
    {
    }

    Iterator(const NCollection_BaseList& theList) noexcept
        : myCurrent(theList.myFirst),
          myPrevious(nullptr)
    {
    }

    void Init(const NCollection_BaseList& theList) noexcept
    {
      myCurrent  = theList.myFirst;
      myPrevious = nullptr;
    }

    void Initialize(const NCollection_BaseList& theList) noexcept { Init(theList); }

    bool More() const noexcept { return (myCurrent != nullptr); }

    bool operator==(const Iterator& theIt) const noexcept { return myCurrent == theIt.myCurrent; }

    bool IsEqual(const Iterator& theOther) const noexcept { return *this == theOther; }

  protected:
    void Init(const NCollection_BaseList& theList, NCollection_ListNode* const thePrev) noexcept
    {
      myCurrent  = thePrev ? thePrev->Next() : (NCollection_ListNode*)theList.PLast();
      myPrevious = thePrev;
    }

  public:
    NCollection_ListNode* myCurrent;
    NCollection_ListNode* myPrevious;
    friend class NCollection_BaseList;
  };

public:
  int Extent() const noexcept { return myLength; }

  bool IsEmpty() const noexcept { return (myFirst == nullptr); }

  const occ::handle<NCollection_BaseAllocator>& Allocator() const noexcept { return myAllocator; }

  virtual ~NCollection_BaseList() = default;

protected:
  NCollection_BaseList(const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
      : myFirst(nullptr),
        myLast(nullptr),
        myLength(0)
  {
    myAllocator =
      (theAllocator.IsNull() ? NCollection_BaseAllocator::CommonBaseAllocator() : theAllocator);
  }

  Standard_EXPORT void PClear(NCollection_DelListNode fDel);

  const NCollection_ListNode* PFirst() const noexcept { return myFirst; }

  const NCollection_ListNode* PLast() const noexcept { return myLast; }

  Standard_EXPORT void PAppend(NCollection_ListNode* theNode) noexcept;

  void PAppend(NCollection_ListNode* theNode, Iterator& theIt) noexcept
  {
    NCollection_ListNode* aPrev = myLast;
    PAppend(theNode);
    theIt.Init(*this, aPrev);
  }

  Standard_EXPORT void PAppend(NCollection_BaseList& theOther) noexcept;

  Standard_EXPORT void PPrepend(NCollection_ListNode* theNode) noexcept;

  Standard_EXPORT void PPrepend(NCollection_BaseList& theOther) noexcept;

  Standard_EXPORT void PRemoveFirst(NCollection_DelListNode fDel);

  Standard_EXPORT void PRemove(Iterator& theIter, NCollection_DelListNode fDel);

  Standard_EXPORT void PInsertBefore(NCollection_ListNode* theNode, Iterator& theIter);

  Standard_EXPORT void PInsertBefore(NCollection_BaseList& theOther, Iterator& theIter);

  Standard_EXPORT void PInsertAfter(NCollection_ListNode* theNode, Iterator& theIter);

  Standard_EXPORT void PInsertAfter(NCollection_BaseList& theOther, Iterator& theIter);

  Standard_EXPORT void PReverse() noexcept;

protected:
  occ::handle<NCollection_BaseAllocator> myAllocator;
  NCollection_ListNode*                  myFirst;
  NCollection_ListNode*                  myLast;
  int                                    myLength;

  friend class Iterator;
};
