#include <NCollection_HeapAllocator.hpp>
#include <Standard_OutOfMemory.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NCollection_HeapAllocator, NCollection_BaseAllocator)

//=================================================================================================

void* NCollection_HeapAllocator::Allocate(const size_t theSize)
{
  // the size is rounded up to word size.
  const size_t aRoundSize = (theSize + 3) & ~0x3;
  void*        aResult    = malloc(aRoundSize);
  if (aResult == nullptr)
  {
    char aBuffer[96];
    Sprintf(aBuffer, "Failed to allocate %" PRIuPTR " bytes in global dynamic heap", theSize);
    throw Standard_OutOfMemory(aBuffer);
  }
  return aResult;
}

//=================================================================================================

void NCollection_HeapAllocator::Free(void* anAddress)
{
  if (anAddress)
    free(anAddress);
}

//=================================================================================================

const occ::handle<NCollection_HeapAllocator>& NCollection_HeapAllocator::GlobalHeapAllocator()
{
  static occ::handle<NCollection_HeapAllocator> pAllocator = new NCollection_HeapAllocator;
  return pAllocator;
}
