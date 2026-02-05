#pragma once

#include <Standard_DefineAlloc.hpp>
#include <Standard_Integer.hpp>

//! The package Standard provides global memory allocator and other basic
//! services used by other OCCT components.

class Standard
{
public:
  DEFINE_STANDARD_ALLOC

  //! Enumiration of possible allocator types
  enum class AllocatorType
  {
    NATIVE   = 0,
    OPT      = 1,
    TBB      = 2,
    JEMALLOC = 3
  };

  //! Returns default allocator type
  Standard_EXPORT static AllocatorType GetAllocatorType();

  //! Allocates memory blocks
  //! theSize - bytes to  allocate
  Standard_EXPORT static void* Allocate(const size_t theSize);

  //! Allocates memory blocks
  //! theSize - bytes to  allocate
  Standard_EXPORT static void* AllocateOptimal(const size_t theSize);

  //! Deallocates memory blocks
  //! @param thePtr - previously allocated memory block to be freed
  Standard_EXPORT static void Free(void* const thePtr);

  //! Template version of function Free(), nullifies the argument pointer
  //! @param thePtr - previously allocated memory block to be freed
  template <typename T>
  static inline void Free(T*& thePtr)
  {
    Free((void*)thePtr);
    thePtr = nullptr;
  }

  //! Reallocates memory blocks
  //! theStorage - previously allocated memory block
  //! theNewSize - new size in bytes
  Standard_EXPORT static void* Reallocate(void* const theStorage, const size_t theNewSize);

  //! Allocates aligned memory blocks.
  //! Should be used with CPU instructions which require specific alignment.
  //! For example: SSE requires 16 bytes, AVX requires 32 bytes.
  //! @param theSize  bytes to allocate
  //! @param theAlign alignment in bytes
  Standard_EXPORT static void* AllocateAligned(const size_t theSize, const size_t theAlign);

  //! Deallocates memory blocks
  //! @param thePtrAligned the memory block previously allocated with AllocateAligned()
  Standard_EXPORT static void FreeAligned(void* const thePtrAligned);

  //! Template version of function FreeAligned(), nullifies the argument pointer
  //! @param thePtrAligned the memory block previously allocated with AllocateAligned()
  template <typename T>
  static inline void FreeAligned(T*& thePtrAligned)
  {
    FreeAligned((void*)thePtrAligned);
    thePtrAligned = nullptr;
  }

  //! Deallocates the storage retained on the free list
  //! and clears the list.
  //! Returns non-zero if some memory has been actually freed.
  Standard_EXPORT static int Purge();

  //! Appends backtrace to a message buffer.
  //! Stack information might be incomplete in case of stripped binaries.
  //! Implementation details:
  //! - Not implemented for Android, iOS, QNX and UWP platforms.
  //! - On non-Windows platform, this function is a wrapper to backtrace() system call.
  //! - On Windows (Win32) platform, the function loads DbgHelp.dll dynamically,
  //!   and no stack will be provided if this or companion libraries (SymSrv.dll, SrcSrv.dll, etc.)
  //!   will not be found; .pdb symbols should be provided on Windows platform to retrieve a
  //!   meaningful stack; only x86_64 CPU architecture is currently implemented.
  //! @param[in][out] theBuffer   message buffer to extend
  //! @param[in] theBufferSize  message buffer size
  //! @param[in] theNbTraces  maximum number of stack traces
  //! @param[in] theContext  optional platform-dependent frame context;
  //!                        in case of DbgHelp (Windows) should be a pointer to CONTEXT
  //! @param[in] theNbTopSkip  number of traces on top of the stack to skip
  //! @return TRUE on success
  Standard_EXPORT static bool StackTrace(char*     theBuffer,
                                         const int theBufferSize,
                                         const int theNbTraces,
                                         void*     theContext   = nullptr,
                                         const int theNbTopSkip = 0);
};
