#pragma once

#include <NCollection_BaseAllocator.hpp>

//! This memory allocator creates dedicated heap for allocations.
//! This technics available only on Windows platform
//! (no alternative on Unix systems).
//! It may be used to take control over memory fragmentation
//! because on destruction ALL allocated memory will be released
//! to the system.
//!
//! This allocator can also be created per each working thread
//! however its real multi-threading performance is dubious.
//!
//! Notice that this also means that existing pointers will be broken
//! and you should control that allocator is alive along all objects
//! allocated with him.
class NCollection_WinHeapAllocator : public NCollection_BaseAllocator
{
public:
  //! Main constructor
  Standard_EXPORT NCollection_WinHeapAllocator(const size_t theInitSizeBytes = 0x80000);

  //! Destructor
  Standard_EXPORT ~NCollection_WinHeapAllocator() override;

  //! Allocate memory
  Standard_EXPORT void* Allocate(const size_t theSize) override;

  //! Allocate memory
  void* AllocateOptimal(const size_t theSize) override { return Allocate(theSize); }

  //! Release memory
  Standard_EXPORT void Free(void* theAddress) override;

  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(NCollection_WinHeapAllocator, NCollection_BaseAllocator)

private:
  //! Copy constructor - prohibited
  NCollection_WinHeapAllocator(const NCollection_WinHeapAllocator&) = delete;

private:
#if (defined(_WIN32) || defined(__WIN32__))
  void* myHeapH;
#endif
  [[maybe_unused]] bool myToZeroMemory;
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
