#pragma once


#include <NCollection_ListNode.hpp>
#include <utility>

/**
 * Purpose:     Abstract list node class. Used by BaseList
 * Remark:      Internal class
 */
template <class TheItemType>
class NCollection_TListNode : public NCollection_ListNode
{
public:
  //! Constructor
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

  //! Constant value access
  const TheItemType& Value() const noexcept { return myValue; }

  //! Variable value access
  TheItemType& ChangeValue() noexcept { return myValue; }

  //! Static deleter to be passed to BaseList
  static void delNode(NCollection_ListNode* theNode, occ::handle<NCollection_BaseAllocator>& theAl)
  {
    ((NCollection_TListNode*)theNode)->myValue.~TheItemType();
    theAl->Free(theNode);
  }

protected:
  TheItemType myValue; //!< The item stored in the node
};

