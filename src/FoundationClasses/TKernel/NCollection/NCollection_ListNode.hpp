#pragma once

#include <NCollection_BaseAllocator.hpp>
#include <NCollection_DefineAlloc.hpp>

class NCollection_ListNode
{
public:
  DEFINE_NCOLLECTION_ALLOC
public:
  NCollection_ListNode(NCollection_ListNode* theNext) noexcept
      : myNext(theNext)
  {
  }

  NCollection_ListNode*& Next() noexcept { return myNext; }

  NCollection_ListNode* Next() const noexcept { return myNext; }

private:
  NCollection_ListNode& operator=(const NCollection_ListNode&) = delete;

  NCollection_ListNode(const NCollection_ListNode&) = delete;

private:
  NCollection_ListNode* myNext;
};
