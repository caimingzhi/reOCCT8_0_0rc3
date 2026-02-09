#pragma once

#include <Standard.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <NCollection_DefineAlloc.hpp>

class NCollection_SeqNode
{
public:
  DEFINE_NCOLLECTION_ALLOC
public:
  NCollection_SeqNode() noexcept
      : myNext(nullptr),
        myPrevious(nullptr)
  {
  }

  NCollection_SeqNode* Next() const noexcept { return myNext; }

  NCollection_SeqNode* Previous() const noexcept { return myPrevious; }

  void SetNext(NCollection_SeqNode* theNext) noexcept { myNext = theNext; }

  void SetPrevious(NCollection_SeqNode* thePrev) noexcept { myPrevious = thePrev; }

private:
  NCollection_SeqNode* myNext;
  NCollection_SeqNode* myPrevious;
};

typedef void (*NCollection_DelSeqNode)(NCollection_SeqNode*,
                                       occ::handle<NCollection_BaseAllocator>& theAl);

class NCollection_BaseSequence
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

    Iterator(const NCollection_BaseSequence& theSeq, const bool isStart) noexcept
    {
      Init(theSeq, isStart);
    }

    void Init(const NCollection_BaseSequence& theSeq, const bool isStart = true) noexcept
    {
      myCurrent  = (isStart ? theSeq.myFirstItem : nullptr);
      myPrevious = (isStart ? nullptr : theSeq.myLastItem);
    }

    void Previous() noexcept
    {
      myCurrent = myPrevious;
      if (myCurrent)
        myPrevious = myCurrent->Previous();
    }

  protected:
    NCollection_SeqNode* myCurrent;
    NCollection_SeqNode* myPrevious;
    friend class NCollection_BaseSequence;
  };

public:
  bool IsEmpty() const noexcept { return (mySize == 0); }

  int Length() const noexcept { return mySize; }

  const occ::handle<NCollection_BaseAllocator>& Allocator() const noexcept { return myAllocator; }

protected:
  NCollection_BaseSequence(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : myFirstItem(nullptr),
        myLastItem(nullptr),
        myCurrentItem(nullptr),
        myCurrentIndex(0),
        mySize(0)
  {
    myAllocator =
      (theAllocator.IsNull() ? NCollection_BaseAllocator::CommonBaseAllocator() : theAllocator);
  }

  virtual ~NCollection_BaseSequence() = default;

  Standard_EXPORT void ClearSeq(NCollection_DelSeqNode fDel);
  Standard_EXPORT void PAppend(NCollection_SeqNode*);
  Standard_EXPORT void PAppend(NCollection_BaseSequence& S);
  Standard_EXPORT void PPrepend(NCollection_SeqNode*);
  Standard_EXPORT void PPrepend(NCollection_BaseSequence& S);
  Standard_EXPORT void PInsertAfter(Iterator& thePosition, NCollection_SeqNode*);
  Standard_EXPORT void PInsertAfter(const int Index, NCollection_SeqNode*);
  Standard_EXPORT void PInsertAfter(const int Index, NCollection_BaseSequence& S);
  Standard_EXPORT void PSplit(const int Index, NCollection_BaseSequence& Sub);
  Standard_EXPORT void RemoveSeq(Iterator& thePosition, NCollection_DelSeqNode fDel);
  Standard_EXPORT void RemoveSeq(const int Index, NCollection_DelSeqNode fDel);
  Standard_EXPORT void RemoveSeq(const int From, const int To, NCollection_DelSeqNode fDel);
  Standard_EXPORT void PReverse() noexcept;
  Standard_EXPORT void PExchange(const int I, const int J);
  Standard_EXPORT NCollection_SeqNode* Find(const int) const noexcept;

protected:
  occ::handle<NCollection_BaseAllocator> myAllocator;
  NCollection_SeqNode*                   myFirstItem;
  NCollection_SeqNode*                   myLastItem;
  NCollection_SeqNode*                   myCurrentItem;
  int                                    myCurrentIndex;
  int                                    mySize;

private:
  NCollection_BaseSequence(const NCollection_BaseSequence& Other) = delete;

  void Nullify() noexcept
  {
    myFirstItem = myLastItem = myCurrentItem = nullptr;
    myCurrentIndex = mySize = 0;
  }

  friend class Iterator;
};
