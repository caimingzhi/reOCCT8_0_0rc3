#include <NCollection_BaseList.hpp>

void NCollection_BaseList::PClear(NCollection_DelListNode fDel)
{
  NCollection_ListNode* pCur  = myFirst;
  NCollection_ListNode* pNext = nullptr;
  while (pCur)
  {
    pNext = pCur->Next();
    fDel(pCur, myAllocator);
    pCur = pNext;
  }
  myLength = 0;
  myFirst = myLast = nullptr;
}

void NCollection_BaseList::PAppend(NCollection_ListNode* theNode) noexcept
{
  if (myLength)
    myLast->Next() = theNode;
  else
    myFirst = theNode;
  theNode->Next() = nullptr;
  myLast          = theNode;
  myLength++;
}

void NCollection_BaseList::PAppend(NCollection_BaseList& theOther) noexcept
{
  if (this == &theOther || theOther.IsEmpty())
    return;

  if (IsEmpty())
    myFirst = theOther.myFirst;
  else
    myLast->Next() = theOther.myFirst;
  myLast           = theOther.myLast;
  theOther.myFirst = theOther.myLast = nullptr;

  myLength += theOther.myLength;
  theOther.myLength = 0;
}

void NCollection_BaseList::PPrepend(NCollection_ListNode* theNode) noexcept
{
  theNode->Next() = myFirst;
  myFirst         = theNode;
  if (myLast == nullptr)
    myLast = myFirst;
  myLength++;
}

void NCollection_BaseList::PPrepend(NCollection_BaseList& theOther) noexcept
{
  if (this == &theOther || theOther.IsEmpty())
    return;

  if (IsEmpty())
    myLast = theOther.myLast;
  else
    theOther.myLast->Next() = myFirst;
  myFirst          = theOther.myFirst;
  theOther.myFirst = theOther.myLast = nullptr;

  myLength += theOther.myLength;
  theOther.myLength = 0;
}

void NCollection_BaseList::PRemoveFirst(NCollection_DelListNode fDel)
{
  Standard_NoSuchObject_Raise_if(IsEmpty(), "NCollection_BaseList::PRemoveFirst");
  NCollection_ListNode* pItem = myFirst;
  myFirst                     = pItem->Next();
  fDel(pItem, myAllocator);
  myLength--;
  if (myLength == 0)
    myLast = nullptr;
}

void NCollection_BaseList::PRemove(Iterator& theIter, NCollection_DelListNode fDel)
{
  Standard_NoSuchObject_Raise_if(!theIter.More(), "NCollection_BaseList::PRemove");
  if (theIter.myPrevious == nullptr)
  {
    PRemoveFirst(fDel);
    theIter.myCurrent = myFirst;
  }
  else
  {
    NCollection_ListNode* pNode  = (theIter.myCurrent)->Next();
    (theIter.myPrevious)->Next() = pNode;
    fDel(theIter.myCurrent, myAllocator);
    theIter.myCurrent = pNode;
    if (pNode == nullptr)
      myLast = theIter.myPrevious;
    myLength--;
  }
}

void NCollection_BaseList::PInsertBefore(NCollection_ListNode* theNode, Iterator& theIter)
{
  Standard_NoSuchObject_Raise_if(!theIter.More(), "NCollection_BaseList::PInsertBefore");
  if (theIter.myPrevious == nullptr)
  {
    PPrepend(theNode);
    theIter.myPrevious = myFirst;
  }
  else
  {
    (theIter.myPrevious)->Next() = theNode;
    theNode->Next()              = theIter.myCurrent;
    theIter.myPrevious           = theNode;
    myLength++;
  }
}

void NCollection_BaseList::PInsertBefore(NCollection_BaseList& theOther, Iterator& theIter)
{
  Standard_NoSuchObject_Raise_if(!theIter.More(), "NCollection_BaseList::PInsertBefore");
  if (theIter.myPrevious == nullptr)
  {
    theIter.myPrevious = theOther.myLast;
    PPrepend(theOther);
  }
  else if (!theOther.IsEmpty())
  {
    myLength += theOther.myLength;
    (theIter.myPrevious)->Next() = theOther.myFirst;
    (theOther.myLast)->Next()    = theIter.myCurrent;
    theIter.myPrevious           = theOther.myLast;
    theOther.myLast = theOther.myFirst = nullptr;
    theOther.myLength                  = 0;
  }
}

void NCollection_BaseList::PInsertAfter(NCollection_ListNode* theNode, Iterator& theIter)
{
  Standard_NoSuchObject_Raise_if(!theIter.More(), "NCollection_BaseList::PInsertAfter");
  if (theIter.myCurrent == myLast)
  {
    PAppend(theNode);
  }
  else
  {
    theNode->Next()             = (theIter.myCurrent)->Next();
    (theIter.myCurrent)->Next() = theNode;
    myLength++;
  }
}

void NCollection_BaseList::PInsertAfter(NCollection_BaseList& theOther, Iterator& theIter)
{
  Standard_NoSuchObject_Raise_if(!theIter.More(), "NCollection_BaseList::PInsertAfter");
  if (theIter.myCurrent == myLast)
  {
    PAppend(theOther);
  }
  else if (!theOther.IsEmpty())
  {
    myLength += theOther.myLength;
    (theOther.myLast)->Next()   = (theIter.myCurrent)->Next();
    (theIter.myCurrent)->Next() = theOther.myFirst;
    theOther.myLast = theOther.myFirst = nullptr;
    theOther.myLength                  = 0;
  }
}

void NCollection_BaseList::PReverse() noexcept
{
  if (myLength > 1)
  {
    NCollection_ListNode* aHead = myFirst->Next();
    NCollection_ListNode* aNeck = myFirst;
    aNeck->Next()               = nullptr;
    while (aHead)
    {
      NCollection_ListNode* aTmp = aHead->Next();
      aHead->Next()              = aNeck;
      aNeck                      = aHead;
      aHead                      = aTmp;
    }
    myLast  = myFirst;
    myFirst = aNeck;
  }
}
