#pragma once

#include <NCollection_BaseAllocator.hpp>

class NCollection_HeapAllocator : public NCollection_BaseAllocator
{
public:
  Standard_EXPORT void* Allocate(const size_t theSize) override;

  void* AllocateOptimal(const size_t theSize) override { return Allocate(theSize); }

  Standard_EXPORT void Free(void* anAddress) override;

  Standard_EXPORT static const occ::handle<NCollection_HeapAllocator>& GlobalHeapAllocator();

protected:
  NCollection_HeapAllocator() {}

private:
  NCollection_HeapAllocator(const NCollection_HeapAllocator&) = delete;

public:
  DEFINE_STANDARD_RTTIEXT(NCollection_HeapAllocator, NCollection_BaseAllocator)
};
