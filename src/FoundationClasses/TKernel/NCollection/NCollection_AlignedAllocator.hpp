#pragma once

#include <NCollection_BaseAllocator.hpp>
#include <Standard.hpp>

class NCollection_AlignedAllocator : public NCollection_BaseAllocator
{
public:
  Standard_EXPORT NCollection_AlignedAllocator(const size_t theAlignment) noexcept;

  Standard_EXPORT void* Allocate(const size_t theSize) override;

  void* AllocateOptimal(const size_t theSize) override { return Allocate(theSize); }

  Standard_EXPORT void Free(void* thePtr) override;

private:
  NCollection_AlignedAllocator(const NCollection_AlignedAllocator&)            = delete;
  NCollection_AlignedAllocator& operator=(const NCollection_AlignedAllocator&) = delete;

protected:
  size_t myAlignment;

public:
  DEFINE_STANDARD_RTTIEXT(NCollection_AlignedAllocator, NCollection_BaseAllocator)
};
