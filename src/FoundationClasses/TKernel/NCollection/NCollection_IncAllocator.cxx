

#include <NCollection_IncAllocator.hpp>

#include <Standard_OutOfMemory.hpp>

#include <cmath>

IMPLEMENT_STANDARD_RTTIEXT(NCollection_IncAllocator, NCollection_BaseAllocator)

namespace
{

  static constexpr unsigned THE_SMALL_BOUND_BLOCK_SIZE =
    NCollection_IncAllocator::THE_DEFAULT_BLOCK_SIZE * 16;
  static constexpr unsigned THE_MEDIUM_BOUND_BLOCK_SIZE =
    NCollection_IncAllocator::THE_DEFAULT_BLOCK_SIZE * 64;
  static constexpr unsigned THE_LARGE_BOUND_BLOCK_SIZE =
    NCollection_IncAllocator::THE_DEFAULT_BLOCK_SIZE * 1024;

  NCollection_IncAllocator::IBlockSizeLevel computeLevel(const unsigned int theSize)
  {
    if (theSize < NCollection_IncAllocator::THE_DEFAULT_BLOCK_SIZE)
    {
      return NCollection_IncAllocator::IBlockSizeLevel::Min;
    }
    else if (theSize < THE_SMALL_BOUND_BLOCK_SIZE)
    {
      return NCollection_IncAllocator::IBlockSizeLevel::Small;
    }
    else if (theSize < THE_MEDIUM_BOUND_BLOCK_SIZE)
    {
      return NCollection_IncAllocator::IBlockSizeLevel::Medium;
    }
    else if (theSize < THE_LARGE_BOUND_BLOCK_SIZE)
    {
      return NCollection_IncAllocator::IBlockSizeLevel::Large;
    }
    else
    {
      return NCollection_IncAllocator::IBlockSizeLevel::Max;
    }
  }
} // namespace

NCollection_IncAllocator::NCollection_IncAllocator(const size_t theDefaultSize)
    : myBlockSize(static_cast<unsigned>(
        theDefaultSize < THE_MINIMUM_BLOCK_SIZE ? THE_DEFAULT_BLOCK_SIZE : theDefaultSize))
{
}

void NCollection_IncAllocator::SetThreadSafe(const bool theIsThreadSafe)
{
  if (theIsThreadSafe)
  {
    if (!myMutex)
    {
      myMutex = opencascade::make_unique<std::mutex>();
    }
  }
  else
  {
    myMutex.reset();
  }
}

NCollection_IncAllocator::~NCollection_IncAllocator()
{
  clean();
}

void* NCollection_IncAllocator::AllocateOptimal(const size_t theSize)
{
  std::unique_lock<std::mutex> aLock =
    myMutex ? std::unique_lock<std::mutex>(*myMutex) : std::unique_lock<std::mutex>();

  IBlock* aBlock = nullptr;

  if (myAllocationHeap && myAllocationHeap->AvailableSize >= theSize)
  {
    aBlock = myAllocationHeap;
  }
  else
  {
    if (++myBlockCount % 5 == 0)
    {
      increaseBlockSize();
    }
    if (myBlockSize < theSize)
    {
      myBlockSize = static_cast<unsigned>(theSize);
    }
    void* aBufferBlock       = Standard::AllocateOptimal(myBlockSize + sizeof(IBlock));
    aBlock                   = new (aBufferBlock) IBlock(aBufferBlock, myBlockSize);
    aBlock->NextBlock        = myAllocationHeap;
    aBlock->NextOrderedBlock = myOrderedBlocks;
    myOrderedBlocks          = aBlock;
    myAllocationHeap         = aBlock;
  }
  void* aRes = aBlock->CurPointer;
  aBlock->CurPointer += theSize;
  aBlock->AvailableSize -= theSize;
  if (aBlock->AvailableSize < 16)
  {
    myAllocationHeap  = aBlock->NextBlock;
    aBlock->NextBlock = myUsedHeap;
    myUsedHeap        = aBlock;
  }
  else
  {
    IBlock* aBlockIter           = aBlock->NextBlock;
    IBlock* aBlockToReplaceAfter = nullptr;
    while (aBlockIter)
    {
      if (aBlockIter->AvailableSize > aBlock->AvailableSize)
      {
        aBlockToReplaceAfter = aBlockIter;
        aBlockIter           = aBlockIter->NextBlock;
        continue;
      }
      break;
    }
    if (aBlockToReplaceAfter)
    {
      IBlock* aNext                   = aBlockToReplaceAfter->NextBlock;
      aBlockToReplaceAfter->NextBlock = aBlock;
      myAllocationHeap                = aBlock->NextBlock;
      aBlock->NextBlock               = aNext;
    }
  }
  return aRes;
}

void* NCollection_IncAllocator::Allocate(const size_t theSize)
{
  return AllocateOptimal(theSize);
}

void NCollection_IncAllocator::clean()
{
  std::unique_lock<std::mutex> aLock =
    myMutex ? std::unique_lock<std::mutex>(*myMutex) : std::unique_lock<std::mutex>();
  IBlock* aHeapIter = myOrderedBlocks;
  while (aHeapIter)
  {
    IBlock* aCur = aHeapIter;
    aHeapIter    = aHeapIter->NextOrderedBlock;
    Standard::Free(aCur);
  }
  myOrderedBlocks  = nullptr;
  myAllocationHeap = nullptr;
  myUsedHeap       = nullptr;
  myBlockCount     = 0;
  myBlockSize      = THE_DEFAULT_BLOCK_SIZE;
}

void NCollection_IncAllocator::increaseBlockSize()
{
  switch (computeLevel(myBlockSize))
  {
    case NCollection_IncAllocator::IBlockSizeLevel::Min:
      myBlockSize *= 8;
      break;
    case NCollection_IncAllocator::IBlockSizeLevel::Small:
      myBlockSize *= 4;
      break;
    case NCollection_IncAllocator::IBlockSizeLevel::Medium:
      myBlockSize *= 2;
      break;
    case NCollection_IncAllocator::IBlockSizeLevel::Large:
      myBlockSize = static_cast<unsigned>(std::lround(myBlockSize * 1.5));
      break;
    case NCollection_IncAllocator::IBlockSizeLevel::Max:
      break;
  }
}

void NCollection_IncAllocator::resetBlock(IBlock* theBlock) const
{
  theBlock->AvailableSize =
    theBlock->AvailableSize
    + (theBlock->CurPointer - (reinterpret_cast<char*>(theBlock) + sizeof(IBlock)));
  theBlock->CurPointer = reinterpret_cast<char*>(theBlock) + sizeof(IBlock);
}

void NCollection_IncAllocator::Reset(const bool theReleaseMemory)
{
  if (theReleaseMemory)
  {
    clean();
    return;
  }
  std::unique_lock<std::mutex> aLock =
    myMutex ? std::unique_lock<std::mutex>(*myMutex) : std::unique_lock<std::mutex>();
  IBlock* aHeapIter = myOrderedBlocks;
  while (aHeapIter)
  {
    IBlock* aCur    = aHeapIter;
    aHeapIter       = aHeapIter->NextOrderedBlock;
    aCur->NextBlock = aHeapIter;
    resetBlock(aCur);
  }
  myAllocationHeap = myOrderedBlocks;
  myUsedHeap       = nullptr;
}

NCollection_IncAllocator::IBlock::IBlock(void* thePointer, const size_t theSize)
    : CurPointer(static_cast<char*>(thePointer) + sizeof(IBlock)),
      AvailableSize(theSize)
{
}
