#pragma once

#include <NCollection_BaseSequence.hpp>
#include <NCollection_StlIterator.hpp>

#include <Standard_OutOfRange.hpp>
#include <Standard_NoSuchObject.hpp>
#include <utility>

template <class TheItemType>
class NCollection_Sequence : public NCollection_BaseSequence
{
public:
  typedef TheItemType value_type;

public:
  class Node : public NCollection_SeqNode
  {
  public:
    Node(const TheItemType& theItem)
        : NCollection_SeqNode()
    {
      myValue = theItem;
    }

    Node(TheItemType&& theItem)
        : NCollection_SeqNode()
    {
      myValue = std::forward<TheItemType>(theItem);
    }

    const TheItemType& Value() const noexcept { return myValue; }

    TheItemType& ChangeValue() noexcept { return myValue; }

  private:
    TheItemType myValue;
  };

public:
  class Iterator : public NCollection_BaseSequence::Iterator
  {
  public:
    Iterator() = default;

    Iterator(const NCollection_Sequence& theSeq, const bool isStart = true)
        : NCollection_BaseSequence::Iterator(theSeq, isStart)
    {
    }

    bool More() const noexcept { return (myCurrent != nullptr); }

    void Next() noexcept
    {
      if (myCurrent)
      {
        myPrevious = myCurrent;
        myCurrent  = myCurrent->Next();
      }
    }

    const TheItemType& Value() const noexcept { return ((const Node*)myCurrent)->Value(); }

    TheItemType& ChangeValue() const noexcept { return ((Node*)myCurrent)->ChangeValue(); }

    bool IsEqual(const Iterator& theOther) const noexcept
    {
      return myCurrent == theOther.myCurrent;
    }
  };

  typedef NCollection_StlIterator<std::bidirectional_iterator_tag, Iterator, TheItemType, false>
    iterator;

  typedef NCollection_StlIterator<std::bidirectional_iterator_tag, Iterator, TheItemType, true>
    const_iterator;

  iterator begin() const noexcept { return Iterator(*this, true); }

  iterator end() const noexcept
  {
    Iterator anIter(*this, false);
    anIter.Next();
    return anIter;
  }

  const_iterator cbegin() const noexcept { return Iterator(*this, true); }

  const_iterator cend() const noexcept
  {
    Iterator anIter(*this, false);
    anIter.Next();
    return anIter;
  }

public:
  NCollection_Sequence()
      : NCollection_BaseSequence(occ::handle<NCollection_BaseAllocator>())
  {
  }

  explicit NCollection_Sequence(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : NCollection_BaseSequence(theAllocator)
  {
  }

  NCollection_Sequence(const NCollection_Sequence& theOther)
      : NCollection_BaseSequence(theOther.myAllocator)
  {
    appendSeq((const Node*)theOther.myFirstItem);
  }

  NCollection_Sequence(NCollection_Sequence&& theOther) noexcept
      : NCollection_BaseSequence(theOther.myAllocator)
  {
    this->operator=(std::forward<NCollection_Sequence>(theOther));
  }

  int Size() const noexcept { return mySize; }

  int Length() const noexcept { return mySize; }

  static constexpr int Lower() noexcept { return 1; }

  int Upper() const noexcept { return mySize; }

  bool IsEmpty() const noexcept { return (mySize == 0); }

  void Reverse() { PReverse(); }

  void Exchange(const int I, const int J) { PExchange(I, J); }

  static void delNode(NCollection_SeqNode* theNode, occ::handle<NCollection_BaseAllocator>& theAl)
  {
    ((Node*)theNode)->~Node();
    theAl->Free(theNode);
  }

  void Clear(const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
  {
    ClearSeq(delNode);
    if (!theAllocator.IsNull())
      this->myAllocator = theAllocator;
  }

  NCollection_Sequence& Assign(const NCollection_Sequence& theOther)
  {
    if (this != &theOther)
    {
      Clear();
      appendSeq((const Node*)theOther.myFirstItem);
    }
    return *this;
  }

  NCollection_Sequence& operator=(const NCollection_Sequence& theOther) { return Assign(theOther); }

  NCollection_Sequence& operator=(NCollection_Sequence&& theOther) noexcept
  {
    if (this == &theOther)
    {
      return *this;
    }
    Clear(theOther.myAllocator);
    myFirstItem    = theOther.myFirstItem;
    myLastItem     = theOther.myLastItem;
    myCurrentItem  = theOther.myCurrentItem;
    myCurrentIndex = theOther.myCurrentIndex;
    mySize         = theOther.mySize;

    theOther.myFirstItem    = nullptr;
    theOther.myLastItem     = nullptr;
    theOther.myCurrentItem  = nullptr;
    theOther.myCurrentIndex = 0;
    theOther.mySize         = 0;
    return *this;
  }

  void Remove(Iterator& thePosition) { RemoveSeq(thePosition, delNode); }

  void Remove(const int theIndex) { RemoveSeq(theIndex, delNode); }

  void Remove(const int theFromIndex, const int theToIndex)
  {
    RemoveSeq(theFromIndex, theToIndex, delNode);
  }

  void Append(const TheItemType& theItem) { PAppend(new (this->myAllocator) Node(theItem)); }

  void Append(TheItemType&& theItem)
  {
    PAppend(new (this->myAllocator) Node(std::forward<TheItemType>(theItem)));
  }

  void Append(NCollection_Sequence& theSeq)
  {
    if (this == &theSeq || theSeq.IsEmpty())
      return;
    if (this->myAllocator == theSeq.myAllocator)
    {

      PAppend(theSeq);
    }
    else
    {

      appendSeq((const Node*)theSeq.myFirstItem);
      theSeq.Clear();
    }
  }

  void Prepend(const TheItemType& theItem) { PPrepend(new (this->myAllocator) Node(theItem)); }

  void Prepend(TheItemType&& theItem)
  {
    PPrepend(new (this->myAllocator) Node(std::forward<TheItemType>(theItem)));
  }

  void Prepend(NCollection_Sequence& theSeq)
  {
    if (this == &theSeq || theSeq.IsEmpty())
      return;
    if (this->myAllocator == theSeq.myAllocator)
    {

      PPrepend(theSeq);
    }
    else
    {

      prependSeq((const Node*)theSeq.myFirstItem, 1);
      theSeq.Clear();
    }
  }

  void InsertBefore(const int theIndex, const TheItemType& theItem)
  {
    InsertAfter(theIndex - 1, theItem);
  }

  void InsertBefore(const int theIndex, TheItemType&& theItem)
  {
    InsertAfter(theIndex - 1, theItem);
  }

  void InsertBefore(const int theIndex, NCollection_Sequence& theSeq)
  {
    InsertAfter(theIndex - 1, theSeq);
  }

  void InsertAfter(Iterator& thePosition, const TheItemType& theItem)
  {
    PInsertAfter(thePosition, new (this->myAllocator) Node(theItem));
  }

  void InsertAfter(Iterator& thePosition, TheItemType&& theItem)
  {
    PInsertAfter(thePosition, new (this->myAllocator) Node(theItem));
  }

  void InsertAfter(const int theIndex, NCollection_Sequence& theSeq)
  {
    if (this == &theSeq || theSeq.IsEmpty())
      return;
    if (this->myAllocator == theSeq.myAllocator)
    {

      PInsertAfter(theIndex, theSeq);
    }
    else
    {

      prependSeq((const Node*)theSeq.myFirstItem, theIndex + 1);
      theSeq.Clear();
    }
  }

  void InsertAfter(const int theIndex, const TheItemType& theItem)
  {
    Standard_OutOfRange_Raise_if(theIndex < 0 || theIndex > mySize,
                                 "NCollection_Sequence::InsertAfter");
    PInsertAfter(theIndex, new (this->myAllocator) Node(theItem));
  }

  void InsertAfter(const int theIndex, TheItemType&& theItem)
  {
    Standard_OutOfRange_Raise_if(theIndex < 0 || theIndex > mySize,
                                 "NCollection_Sequence::InsertAfter");
    PInsertAfter(theIndex, new (this->myAllocator) Node(theItem));
  }

  void Split(const int theIndex, NCollection_Sequence& theSeq)
  {
    theSeq.Clear(this->myAllocator);
    PSplit(theIndex, theSeq);
  }

  const TheItemType& First() const
  {
    Standard_NoSuchObject_Raise_if(mySize == 0, "NCollection_Sequence::First");
    return ((const Node*)myFirstItem)->Value();
  }

  TheItemType& ChangeFirst()
  {
    Standard_NoSuchObject_Raise_if(mySize == 0, "NCollection_Sequence::ChangeFirst");
    return ((Node*)myFirstItem)->ChangeValue();
  }

  const TheItemType& Last() const
  {
    Standard_NoSuchObject_Raise_if(mySize == 0, "NCollection_Sequence::Last");
    return ((const Node*)myLastItem)->Value();
  }

  TheItemType& ChangeLast()
  {
    Standard_NoSuchObject_Raise_if(mySize == 0, "NCollection_Sequence::ChangeLast");
    return ((Node*)myLastItem)->ChangeValue();
  }

  const TheItemType& Value(const int theIndex) const
  {
    Standard_OutOfRange_Raise_if(theIndex <= 0 || theIndex > mySize, "NCollection_Sequence::Value");

    NCollection_Sequence* const aLocalTHIS = (NCollection_Sequence*)this;
    aLocalTHIS->myCurrentItem              = Find(theIndex);
    aLocalTHIS->myCurrentIndex             = theIndex;
    return ((const Node*)myCurrentItem)->Value();
  }

  const TheItemType& operator()(const int theIndex) const { return Value(theIndex); }

  TheItemType& ChangeValue(const int theIndex)
  {
    Standard_OutOfRange_Raise_if(theIndex <= 0 || theIndex > mySize,
                                 "NCollection_Sequence::ChangeValue");

    myCurrentItem  = Find(theIndex);
    myCurrentIndex = theIndex;
    return ((Node*)myCurrentItem)->ChangeValue();
  }

  TheItemType& operator()(const int theIndex) { return ChangeValue(theIndex); }

  void SetValue(const int theIndex, const TheItemType& theItem) { ChangeValue(theIndex) = theItem; }

  ~NCollection_Sequence() override { Clear(); }

private:
  friend class Iterator;

  void appendSeq(const Node* pCur)
  {
    while (pCur)
    {
      Node* pNew = new (this->myAllocator) Node(pCur->Value());
      PAppend(pNew);
      pCur = (const Node*)pCur->Next();
    }
  }

  void prependSeq(const Node* pCur, int ind)
  {
    ind--;
    while (pCur)
    {
      Node* pNew = new (this->myAllocator) Node(pCur->Value());
      PInsertAfter(ind++, pNew);
      pCur = (const Node*)pCur->Next();
    }
  }
};
