

#include <NCollection_BaseAllocator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NCollection_BaseAllocator, Standard_Transient)

void* NCollection_BaseAllocator::Allocate(const size_t theSize)
{
  return Standard::Allocate(theSize);
}

void* NCollection_BaseAllocator::AllocateOptimal(const size_t theSize)
{
  return Standard::AllocateOptimal(theSize);
}

void NCollection_BaseAllocator::Free(void* theAddress)
{
  Standard::Free(theAddress);
}

const occ::handle<NCollection_BaseAllocator>& NCollection_BaseAllocator::CommonBaseAllocator()
{
  static occ::handle<NCollection_BaseAllocator> THE_SINGLETON_ALLOC = new NCollection_BaseAllocator;
  return THE_SINGLETON_ALLOC;
}
