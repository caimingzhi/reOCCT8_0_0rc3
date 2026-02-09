#pragma once

#include <NCollection_BaseList.hpp>
#include <NCollection_TListNode.hpp>

template <class TheItemType>
class NCollection_TListIterator : public NCollection_BaseList::Iterator
{
public:
  NCollection_TListIterator() noexcept
      : NCollection_BaseList::Iterator()
  {
  }

  NCollection_TListIterator(const NCollection_BaseList& theList) noexcept
      : NCollection_BaseList::Iterator(theList)
  {
  }

  bool More() const noexcept { return (myCurrent != nullptr); }

  void Next() noexcept
  {
    myPrevious = myCurrent;
    myCurrent  = myCurrent->Next();
  }

  const TheItemType& Value() const noexcept
  {
    return ((const NCollection_TListNode<TheItemType>*)myCurrent)->Value();
  }

  TheItemType& Value() noexcept
  {
    return ((NCollection_TListNode<TheItemType>*)myCurrent)->ChangeValue();
  }

  TheItemType& ChangeValue() const noexcept
  {
    return ((NCollection_TListNode<TheItemType>*)myCurrent)->ChangeValue();
  }
};

#include <NCollection_StlIterator.hpp>

#include <Standard_NoSuchObject.hpp>

template <class TheItemType>
class NCollection_List : public NCollection_BaseList
{
public:
  typedef TheItemType value_type;

public:
  typedef NCollection_TListNode<TheItemType>     ListNode;
  typedef NCollection_TListIterator<TheItemType> Iterator;

  typedef NCollection_StlIterator<std::forward_iterator_tag, Iterator, TheItemType, false> iterator;

  typedef NCollection_StlIterator<std::forward_iterator_tag, Iterator, TheItemType, true>
    const_iterator;

  iterator begin() const noexcept { return Iterator(*this); }

  iterator end() const noexcept { return Iterator(); }

  const_iterator cbegin() const noexcept { return Iterator(*this); }

  const_iterator cend() const noexcept { return Iterator(); }

public:
  NCollection_List()
      : NCollection_BaseList(occ::handle<NCollection_BaseAllocator>())
  {
  }

  explicit NCollection_List(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : NCollection_BaseList(theAllocator)
  {
  }

  NCollection_List(const NCollection_List& theOther)
      : NCollection_BaseList(theOther.myAllocator)
  {
    appendList(theOther.PFirst());
  }

  NCollection_List(NCollection_List&& theOther) noexcept
      : NCollection_BaseList(theOther.myAllocator)
  {
    this->operator=(std::forward<NCollection_List>(theOther));
  }

  int Size() const noexcept { return Extent(); }

  NCollection_List& Assign(const NCollection_List& theOther)
  {
    if (this != &theOther)
    {
      Clear();
      appendList(theOther.PFirst());
    }
    return *this;
  }

  NCollection_List& operator=(const NCollection_List& theOther) { return Assign(theOther); }

  NCollection_List& operator=(NCollection_List&& theOther) noexcept
  {
    if (this == &theOther)
    {
      return *this;
    }
    Clear(theOther.myAllocator);
    myFirst          = theOther.myFirst;
    myLast           = theOther.myLast;
    myLength         = theOther.myLength;
    theOther.myFirst = theOther.myLast = nullptr;
    theOther.myLength                  = 0;
    return *this;
  }

  void Clear(const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
  {
    PClear(ListNode::delNode);
    if (!theAllocator.IsNull())
      this->myAllocator = theAllocator;
  }

  const TheItemType& First() const
  {
    Standard_NoSuchObject_Raise_if(IsEmpty(), "NCollection_List::First");
    return ((const ListNode*)PFirst())->Value();
  }

  TheItemType& First()
  {
    Standard_NoSuchObject_Raise_if(IsEmpty(), "NCollection_List::First");
    return ((ListNode*)PFirst())->ChangeValue();
  }

  const TheItemType& Last() const
  {
    Standard_NoSuchObject_Raise_if(IsEmpty(), "NCollection_List::Last");
    return ((const ListNode*)PLast())->Value();
  }

  TheItemType& Last()
  {
    Standard_NoSuchObject_Raise_if(IsEmpty(), "NCollection_List::Last");
    return ((ListNode*)PLast())->ChangeValue();
  }

  TheItemType& Append(const TheItemType& theItem)
  {
    ListNode* pNew = new (this->myAllocator) ListNode(theItem);
    PAppend(pNew);
    return ((ListNode*)PLast())->ChangeValue();
  }

  TheItemType& Append(TheItemType&& theItem)
  {
    ListNode* pNew = new (this->myAllocator) ListNode(std::forward<TheItemType>(theItem));
    PAppend(pNew);
    return ((ListNode*)PLast())->ChangeValue();
  }

  void Append(const TheItemType& theItem, Iterator& theIter)
  {
    ListNode* pNew = new (this->myAllocator) ListNode(theItem);
    PAppend(pNew, theIter);
  }

  void Append(TheItemType&& theItem, Iterator& theIter)
  {
    ListNode* pNew = new (this->myAllocator) ListNode(std::forward<TheItemType>(theItem));
    PAppend(pNew, theIter);
  }

  void Append(NCollection_List& theOther)
  {
    if (this == &theOther || theOther.Extent() < 1)
      return;
    if (this->myAllocator == theOther.myAllocator)
    {

      PAppend(theOther);
    }
    else
    {

      appendList(theOther.myFirst);
      theOther.Clear();
    }
  }

  TheItemType& Prepend(const TheItemType& theItem)
  {
    ListNode* pNew = new (this->myAllocator) ListNode(theItem);
    PPrepend(pNew);
    return ((ListNode*)PFirst())->ChangeValue();
  }

  TheItemType& Prepend(TheItemType&& theItem)
  {
    ListNode* pNew = new (this->myAllocator) ListNode(std::forward<TheItemType>(theItem));
    PPrepend(pNew);
    return ((ListNode*)PFirst())->ChangeValue();
  }

  void Prepend(NCollection_List& theOther)
  {
    if (this == &theOther || theOther.Extent() < 1)
      return;
    if (this->myAllocator == theOther.myAllocator)
    {

      PPrepend(theOther);
    }
    else
    {

      Iterator it(*this);
      prependList(theOther.PFirst(), it);
      theOther.Clear();
    }
  }

  void RemoveFirst() { PRemoveFirst(ListNode::delNode); }

  void Remove(Iterator& theIter) { PRemove(theIter, ListNode::delNode); }

  template <typename TheValueType>

  bool Remove(const TheValueType& theObject)
  {
    for (Iterator anIter(*this); anIter.More(); anIter.Next())
    {
      if (anIter.Value() == theObject)
      {
        Remove(anIter);
        return true;
      }
    }
    return false;
  }

  TheItemType& InsertBefore(const TheItemType& theItem, Iterator& theIter)
  {
    ListNode* pNew = new (this->myAllocator) ListNode(theItem);
    PInsertBefore(pNew, theIter);
    return pNew->ChangeValue();
  }

  TheItemType& InsertBefore(TheItemType&& theItem, Iterator& theIter)
  {
    ListNode* pNew = new (this->myAllocator) ListNode(std::forward<TheItemType>(theItem));
    PInsertBefore(pNew, theIter);
    return pNew->ChangeValue();
  }

  void InsertBefore(NCollection_List& theOther, Iterator& theIter)
  {
    if (this == &theOther)
      return;

    if (this->myAllocator == theOther.myAllocator)
    {

      PInsertBefore(theOther, theIter);
    }
    else
    {

      prependList(theOther.myFirst, theIter);
      theOther.Clear();
    }
  }

  TheItemType& InsertAfter(const TheItemType& theItem, Iterator& theIter)
  {
    ListNode* pNew = new (this->myAllocator) ListNode(theItem);
    PInsertAfter(pNew, theIter);
    return pNew->ChangeValue();
  }

  TheItemType& InsertAfter(TheItemType&& theItem, Iterator& theIter)
  {
    ListNode* pNew = new (this->myAllocator) ListNode(std::forward<TheItemType>(theItem));
    PInsertAfter(pNew, theIter);
    return pNew->ChangeValue();
  }

  void InsertAfter(NCollection_List& theOther, Iterator& theIter)
  {
    if (!theIter.More())
    {
      Append(theOther);
      return;
    }
    if (this->myAllocator == theOther.myAllocator)
    {

      PInsertAfter(theOther, theIter);
    }
    else
    {

      Iterator anIter;
      anIter.myPrevious = theIter.myCurrent;
      anIter.myCurrent  = theIter.myCurrent->Next();
      prependList(theOther.PFirst(), anIter);
      theOther.Clear();
    }
  }

  void Reverse() { PReverse(); }

  template <typename TheValueType>

  bool Contains(const TheValueType& theObject) const
  {
    for (Iterator anIter(*this); anIter.More(); anIter.Next())
    {
      if (anIter.Value() == theObject)
      {
        return true;
      }
    }
    return false;
  }

  ~NCollection_List() override { Clear(); }

private:
  void appendList(const NCollection_ListNode* pCur)
  {
    while (pCur)
    {
      NCollection_ListNode* pNew =
        new (this->myAllocator) ListNode(((const ListNode*)(pCur))->Value());
      PAppend(pNew);
      pCur = pCur->Next();
    }
  }

  void prependList(const NCollection_ListNode* pCur, Iterator& theIter)
  {
    while (pCur)
    {
      NCollection_ListNode* pNew =
        new (this->myAllocator) ListNode(((const ListNode*)(pCur))->Value());
      PInsertBefore(pNew, theIter);
      pCur = pCur->Next();
    }
  }
};
