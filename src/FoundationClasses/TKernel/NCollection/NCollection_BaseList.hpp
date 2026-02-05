#pragma once

#include <Standard_NoSuchObject.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <NCollection_ListNode.hpp>

typedef void (*NCollection_DelListNode)(NCollection_ListNode*,
                                        occ::handle<NCollection_BaseAllocator>& theAl);

// ********************************************************** BaseList class
class NCollection_BaseList
{
public:
  //! Memory allocation
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

public:
  class Iterator
  {
  public:
    // ******** Empty constructor
    Iterator() noexcept
        : myCurrent(nullptr),
          myPrevious(nullptr)
    {
    }

    // ******** Constructor with initialisation
    Iterator(const NCollection_BaseList& theList) noexcept
        : myCurrent(theList.myFirst),
          myPrevious(nullptr)
    {
    }

    // ******** Initialisation
    void Init(const NCollection_BaseList& theList) noexcept
    {
      myCurrent  = theList.myFirst;
      myPrevious = nullptr;
    }

    // ******** Initialisation
    void Initialize(const NCollection_BaseList& theList) noexcept { Init(theList); }

    // ******** More
    bool More() const noexcept { return (myCurrent != nullptr); }

    // ******** Comparison operator
    bool operator==(const Iterator& theIt) const noexcept { return myCurrent == theIt.myCurrent; }

    //! Performs comparison of two iterators
    bool IsEqual(const Iterator& theOther) const noexcept { return *this == theOther; }

  protected:
    void Init(const NCollection_BaseList& theList, NCollection_ListNode* const thePrev) noexcept
    {
      myCurrent  = thePrev ? thePrev->Next() : (NCollection_ListNode*)theList.PLast();
      myPrevious = thePrev;
    }

  public:
    NCollection_ListNode* myCurrent;  // Pointer to the current node
    NCollection_ListNode* myPrevious; // Pointer to the previous one
    friend class NCollection_BaseList;
  }; // End of nested class Iterator

public:
  // ---------- PUBLIC METHODS ------------
  // ******** Extent
  // Purpose: Returns the number of nodes in the list
  int Extent() const noexcept { return myLength; }

  // ******** IsEmpty
  // Purpose: Query if the list is empty
  bool IsEmpty() const noexcept { return (myFirst == nullptr); }

  // ******** Allocator
  //! Returns attached allocator
  const occ::handle<NCollection_BaseAllocator>& Allocator() const noexcept { return myAllocator; }

  // ******** Destructor
  // Purpose: defines virtual interface
  virtual ~NCollection_BaseList() = default;

protected:
  // --------- PROTECTED METHODS ----------

  // ******** Constructor
  // Purpose: Initializes an empty list
  NCollection_BaseList(const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
      : myFirst(nullptr),
        myLast(nullptr),
        myLength(0)
  {
    myAllocator =
      (theAllocator.IsNull() ? NCollection_BaseAllocator::CommonBaseAllocator() : theAllocator);
  }

  // ******** PClear
  // Purpose: deletes all nodes
  Standard_EXPORT void PClear(NCollection_DelListNode fDel);

  // ******** PFirst
  // Purpose: Returns pointer to the first node
  const NCollection_ListNode* PFirst() const noexcept { return myFirst; }

  // ******** PLast
  // Purpose: Returns pointer to the last node
  const NCollection_ListNode* PLast() const noexcept { return myLast; }

  // ******** PAppend
  // Purpose: Appends theNode at the end
  Standard_EXPORT void PAppend(NCollection_ListNode* theNode) noexcept;

  // ******** PAppend
  // Purpose: Appends theNode at the end, returns iterator to the previous
  void PAppend(NCollection_ListNode* theNode, Iterator& theIt) noexcept
  {
    NCollection_ListNode* aPrev = myLast;
    PAppend(theNode);
    theIt.Init(*this, aPrev);
  }

  // ******** PAppend
  // Purpose: Appends theOther list at the end (clearing it)
  Standard_EXPORT void PAppend(NCollection_BaseList& theOther) noexcept;

  // ******** PPrepend
  // Purpose: Prepends theNode at the beginning
  Standard_EXPORT void PPrepend(NCollection_ListNode* theNode) noexcept;

  // ******** PPrepend
  // Purpose: Prepends theOther list at the beginning (clearing it)
  Standard_EXPORT void PPrepend(NCollection_BaseList& theOther) noexcept;

  // ******** PRemoveFirst
  // Purpose: Removes first node
  Standard_EXPORT void PRemoveFirst(NCollection_DelListNode fDel);

  // ******** PRemove
  // Purpose: Removes the node pointed by theIter[ator]
  Standard_EXPORT void PRemove(Iterator& theIter, NCollection_DelListNode fDel);

  // ******** PInsertBefore
  // Purpose: Inserts theNode before one pointed by theIter[ator]
  Standard_EXPORT void PInsertBefore(NCollection_ListNode* theNode, Iterator& theIter);

  // ******** PInsertBefore
  // Purpose: Inserts theOther list before the node pointed by theIter[ator]
  Standard_EXPORT void PInsertBefore(NCollection_BaseList& theOther, Iterator& theIter);

  // ******** PInsertAfter
  // Purpose: Inserts theNode after one pointed by theIter[ator]
  Standard_EXPORT void PInsertAfter(NCollection_ListNode* theNode, Iterator& theIter);

  // ******** PInsertAfter
  // Purpose: Inserts theOther list after the node pointed by theIter[ator]
  Standard_EXPORT void PInsertAfter(NCollection_BaseList& theOther, Iterator& theIter);

  // ******** PReverse
  // Purpose: Reverse the list
  Standard_EXPORT void PReverse() noexcept;

protected:
  // ------------ PROTECTED FIELDS ------------
  occ::handle<NCollection_BaseAllocator> myAllocator;
  NCollection_ListNode*                  myFirst;  // Pointer to the head
  NCollection_ListNode*                  myLast;   // Pointer to the tail
  int                                    myLength; // Actual length

  // ------------ FRIEND CLASSES ------------
  friend class Iterator;
};
