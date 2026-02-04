#pragma once


#include <NCollection_BaseAllocator.hpp>
#include <Standard.hpp>

//! NCollection allocator with managed memory alignment capabilities.
class NCollection_AlignedAllocator : public NCollection_BaseAllocator
{
public:
  //! Constructor. The alignment should be specified explicitly:
  //! 16 bytes for SSE instructions
  //! 32 bytes for AVX instructions
  Standard_EXPORT NCollection_AlignedAllocator(const size_t theAlignment) noexcept;

  //! Allocate memory with given size. Returns NULL on failure.
  Standard_EXPORT void* Allocate(const size_t theSize) override;

  //! Allocate memory with given size. Returns NULL on failure.
  void* AllocateOptimal(const size_t theSize) override { return Allocate(theSize); }

  //! Free a previously allocated memory.
  Standard_EXPORT void Free(void* thePtr) override;

private:
  NCollection_AlignedAllocator(const NCollection_AlignedAllocator&)            = delete;
  NCollection_AlignedAllocator& operator=(const NCollection_AlignedAllocator&) = delete;

protected:
  size_t myAlignment; //!< alignment in bytes

public:
  DEFINE_STANDARD_RTTIEXT(NCollection_AlignedAllocator, NCollection_BaseAllocator)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
