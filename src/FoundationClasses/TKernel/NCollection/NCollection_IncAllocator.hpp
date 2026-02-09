#pragma once

#include <NCollection_BaseAllocator.hpp>
#include <NCollection_OccAllocator.hpp>
#include <NCollection_Allocator.hpp>
#include <Standard_MemoryUtils.hpp>

#include <utility>
#include <mutex>

class NCollection_IncAllocator : public NCollection_BaseAllocator
{
public:
  Standard_EXPORT NCollection_IncAllocator(const size_t theBlockSize = THE_DEFAULT_BLOCK_SIZE);

  Standard_EXPORT void SetThreadSafe(const bool theIsThreadSafe = true);

  Standard_EXPORT void* Allocate(const size_t size) override;

  Standard_EXPORT void* AllocateOptimal(const size_t size) override;

  void Free(void*) override {}

  Standard_EXPORT ~NCollection_IncAllocator() override;

  Standard_EXPORT void Reset(const bool theReleaseMemory = false);

private:
  NCollection_IncAllocator(const NCollection_IncAllocator&)            = delete;
  NCollection_IncAllocator& operator=(const NCollection_IncAllocator&) = delete;

public:
  struct IBlock
  {
    IBlock(void* thePointer, const size_t theSize);

    char*   CurPointer;
    size_t  AvailableSize;
    IBlock* NextBlock        = nullptr;
    IBlock* NextOrderedBlock = nullptr;
  };

  enum class IBlockSizeLevel : unsigned short
  {
    Min = 0,
    Small,
    Medium,
    Large,
    Max
  };

protected:
  void increaseBlockSize();

  void resetBlock(IBlock* theBlock) const;

  void clean();

public:
  static constexpr size_t THE_DEFAULT_BLOCK_SIZE = 1024 * 12;

  static constexpr size_t THE_MINIMUM_BLOCK_SIZE = 1024 * 2;

private:
  unsigned int                myBlockSize;
  unsigned int                myBlockCount     = 0;
  std::unique_ptr<std::mutex> myMutex          = nullptr;
  IBlock*                     myAllocationHeap = nullptr;
  IBlock*                     myUsedHeap       = nullptr;
  IBlock*                     myOrderedBlocks  = nullptr;

public:
  DEFINE_STANDARD_RTTIEXT(NCollection_IncAllocator, NCollection_BaseAllocator)
};
