#pragma once

#include <NCollection_BaseAllocator.hpp>

// Macro to overload placement new and delete operators for NCollection allocators.
// For Borland C and old SUN compilers do not define placement delete
// as it is not supported.
#if defined(__BORLANDC__) || (defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530))
  #define DEFINE_NCOLLECTION_ALLOC                                                                 \
    void* operator new(size_t theSize, const occ::handle<NCollection_BaseAllocator>& theAllocator) \
    {                                                                                              \
      return theAllocator->Allocate(theSize);                                                      \
    }
#else
  #define DEFINE_NCOLLECTION_ALLOC                                                                 \
    void* operator new(size_t theSize, const occ::handle<NCollection_BaseAllocator>& theAllocator) \
    {                                                                                              \
      return theAllocator->Allocate(theSize);                                                      \
    }                                                                                              \
    void operator delete(void*                                         theAddress,                 \
                         const occ::handle<NCollection_BaseAllocator>& theAllocator)               \
    {                                                                                              \
      theAllocator->Free(theAddress);                                                              \
    }
#endif
