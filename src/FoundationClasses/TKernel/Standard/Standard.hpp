#pragma once

#include <Standard_DefineAlloc.hpp>
#include <Standard_Integer.hpp>

class Standard
{
public:
  DEFINE_STANDARD_ALLOC

  enum class AllocatorType
  {
    NATIVE   = 0,
    OPT      = 1,
    TBB      = 2,
    JEMALLOC = 3
  };

  Standard_EXPORT static AllocatorType GetAllocatorType();

  Standard_EXPORT static void* Allocate(const size_t theSize);

  Standard_EXPORT static void* AllocateOptimal(const size_t theSize);

  Standard_EXPORT static void Free(void* const thePtr);

  template <typename T>
  static inline void Free(T*& thePtr)
  {
    Free((void*)thePtr);
    thePtr = nullptr;
  }

  Standard_EXPORT static void* Reallocate(void* const theStorage, const size_t theNewSize);

  Standard_EXPORT static void* AllocateAligned(const size_t theSize, const size_t theAlign);

  Standard_EXPORT static void FreeAligned(void* const thePtrAligned);

  template <typename T>
  static inline void FreeAligned(T*& thePtrAligned)
  {
    FreeAligned((void*)thePtrAligned);
    thePtrAligned = nullptr;
  }

  Standard_EXPORT static int Purge();

  Standard_EXPORT static bool StackTrace(char*     theBuffer,
                                         const int theBufferSize,
                                         const int theNbTraces,
                                         void*     theContext   = nullptr,
                                         const int theNbTopSkip = 0);
};
