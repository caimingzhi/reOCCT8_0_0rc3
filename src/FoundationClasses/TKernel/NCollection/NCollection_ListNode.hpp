#pragma once

#include <NCollection_BaseAllocator.hpp>
#include <NCollection_DefineAlloc.hpp>

/**
 * Purpose:     This class is used to  represent a node  in the BaseList and
 *              BaseMap.
 */
class NCollection_ListNode
{
public:
  // define new operator for use with NCollection allocators
  DEFINE_NCOLLECTION_ALLOC
public:
  //! The only constructor
  NCollection_ListNode(NCollection_ListNode* theNext) noexcept
      : myNext(theNext)
  {
  }

  //! Next pointer access
  NCollection_ListNode*& Next() noexcept { return myNext; }

  //! Next pointer const access
  NCollection_ListNode* Next() const noexcept { return myNext; }

private:
  //! operator= - forbidden
  NCollection_ListNode& operator=(const NCollection_ListNode&) = delete;

  //! copy constructor - forbidden
  NCollection_ListNode(const NCollection_ListNode&) = delete;

private:
  NCollection_ListNode* myNext; //!< Pointer to the next node
};
