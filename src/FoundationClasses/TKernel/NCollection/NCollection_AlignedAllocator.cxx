#include <NCollection_AlignedAllocator.hpp>
#include <NCollection_Buffer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NCollection_AlignedAllocator, NCollection_BaseAllocator)

NCollection_AlignedAllocator::NCollection_AlignedAllocator(const size_t theAlignment) noexcept
    : myAlignment(theAlignment)
{
}

void* NCollection_AlignedAllocator::Allocate(const size_t theSize)
{
  return Standard::AllocateAligned(theSize, myAlignment);
}

void NCollection_AlignedAllocator::Free(void* thePtr)
{
  Standard::FreeAligned(thePtr);
}
