#pragma once

#include <NCollection_BaseAllocator.hpp>

class NCollection_WinHeapAllocator : public NCollection_BaseAllocator
{
public:
  Standard_EXPORT NCollection_WinHeapAllocator(const size_t theInitSizeBytes = 0x80000);

  Standard_EXPORT ~NCollection_WinHeapAllocator() override;

  Standard_EXPORT void* Allocate(const size_t theSize) override;

  void* AllocateOptimal(const size_t theSize) override { return Allocate(theSize); }

  Standard_EXPORT void Free(void* theAddress) override;

  DEFINE_STANDARD_RTTIEXT(NCollection_WinHeapAllocator, NCollection_BaseAllocator)

private:
  NCollection_WinHeapAllocator(const NCollection_WinHeapAllocator&) = delete;

private:
#if (defined(_WIN32) || defined(__WIN32__))
  void* myHeapH;
#endif
  [[maybe_unused]] bool myToZeroMemory;
};
