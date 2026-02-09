#pragma once

#include <NCollection_ListNode.hpp>
#include <utility>

template <class TheItemType>
class NCollection_TListNode : public NCollection_ListNode
{
public:
  NCollection_TListNode(const TheItemType& theItem, NCollection_ListNode* theNext = nullptr)
      : NCollection_ListNode(theNext),
        myValue(theItem)
  {
  }

  NCollection_TListNode(TheItemType&& theItem, NCollection_ListNode* theNext = nullptr)
      : NCollection_ListNode(theNext),
        myValue(std::forward<TheItemType>(theItem))
  {
  }

  const TheItemType& Value() const noexcept { return myValue; }

  TheItemType& ChangeValue() noexcept { return myValue; }

  static void delNode(NCollection_ListNode* theNode, occ::handle<NCollection_BaseAllocator>& theAl)
  {
    ((NCollection_TListNode*)theNode)->myValue.~TheItemType();
    theAl->Free(theNode);
  }

protected:
  TheItemType myValue;
};
