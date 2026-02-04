#pragma once


#include <NCollection_BaseAllocator.hpp>

/**
 * Allocator that uses the global dynamic heap (malloc / free).
 */

class NCollection_HeapAllocator : public NCollection_BaseAllocator
{
public:
  // ---------- PUBLIC METHODS ----------
  Standard_EXPORT void* Allocate(const size_t theSize) override;

  void* AllocateOptimal(const size_t theSize) override { return Allocate(theSize); }

  Standard_EXPORT void Free(void* anAddress) override;

  Standard_EXPORT static const occ::handle<NCollection_HeapAllocator>& GlobalHeapAllocator();

protected:
  //! Constructor - prohibited
  NCollection_HeapAllocator() {}

private:
  //! Copy constructor - prohibited
  NCollection_HeapAllocator(const NCollection_HeapAllocator&) = delete;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(NCollection_HeapAllocator, NCollection_BaseAllocator)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
