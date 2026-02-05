#include <NCollection_AccAllocator.hpp>
#include <Standard_OutOfMemory.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NCollection_AccAllocator, NCollection_BaseAllocator)

//=================================================================================================

NCollection_AccAllocator::NCollection_AccAllocator(const size_t theBlockSize)
    : myBlockSize(theBlockSize),
      mypLastBlock(nullptr)
{
  allocateNewBlock(myBlockSize);
}

//=================================================================================================

NCollection_AccAllocator::~NCollection_AccAllocator()
{
  for (Block* aBlock = mypLastBlock; aBlock; aBlock = aBlock->prevBlock)
  {
    Standard::Free(aBlock->address);
  }
}

//=================================================================================================

void* NCollection_AccAllocator::Allocate(const size_t theSize)
{
  const AlignedSize aSize(theSize);
  Block*            aBlock;

  if (aSize <= mypLastBlock->FreeSize())
  {
    aBlock = mypLastBlock;
  }
  else if (aSize > myBlockSize)
  {
    // If the requested size exceeds normal allocation size,
    // allocate a separate block
    aBlock = allocateNewBlock(aSize);
  }
  else
  {
    // Search for a block in the list with enough free space
    int aBlocksRest = MaxLookupBlocks;
    for (aBlock = mypLastBlock->prevBlock; aBlock != nullptr && --aBlocksRest;
         aBlock = aBlock->prevBlock)
    {
      if (aSize <= aBlock->FreeSize())
        break;
    }
    if (aBlock == nullptr || !aBlocksRest)
      // There is no available block with enough free space, create a new one
      aBlock = allocateNewBlock(myBlockSize);
  }

  void* anAddress = aBlock->Allocate(aSize);
#ifdef OCCT_DEBUG_FINDBLOCK
  Key aKey;
  Standard_ASSERT_VOID(aBlock == findBlock(anAddress, aKey),
                       "improper work of NCollection_AccAllocator::findBlock");
#endif
  return anAddress;
}

//=======================================================================
// function : Free
// purpose  : Free a previously allocated memory
//=======================================================================
void NCollection_AccAllocator::Free(void* theAddress)
{
  Key    aKey{};
  Block* aBlock = findBlock(theAddress, aKey);

#if !defined No_Exception && !defined No_Standard_ProgramError
  if (aBlock == nullptr || aBlock->IsEmpty())
  {
    throw Standard_ProgramError("NCollection_AccAllocator::Free: \
                                Trying to free an invalid address");
  }
#endif

  aBlock->Free();
  if (aBlock->IsEmpty())
  {
    void* anAddress = aBlock->address;

    // Deallocate and remove the free block if there are more blocks
    if (myBlocks.Size() > 1)
    {
      Standard::Free(anAddress);
      Block** appBlock;
      for (appBlock = &mypLastBlock; *appBlock != nullptr; appBlock = &(*appBlock)->prevBlock)
      {
        if (*appBlock == aBlock)
        {
          *appBlock = aBlock->prevBlock;
          break;
        }
      }
      myBlocks.UnBind(aKey);
    }
    // If there are no more blocks, reallocate the block to the default size
    else
    {
      const size_t aRoundSize  = (myBlockSize + 3) & ~0x3;
      void*        aNewAddress = Standard::Reallocate(anAddress, aRoundSize);
      if (aNewAddress == anAddress)
      {
        // Normally, the reallocation keeps the block at the same address
        // (since no block can be smaller than the default size, and thus
        // the allocated memory is just shrunk or untouched).
        // In this case, just update the block's free size.
        aBlock->SetFreeSize(myBlockSize);
      }
      else
      {
        // Reallocation still may return a different address even if the new
        // size is equal to or smaller than the old one (this can happen in
        // debug mode).
        Key aNewKey = getKey(aNewAddress);
        if (aNewKey.Value == aKey.Value)
        {
          // If the new address have the same key,
          // just update the block's address and free size
          aBlock->address = aNewAddress;
          aBlock->SetFreeSize(myBlockSize);
        }
        else
        {
          // If the new address have different key,
          // rebind the block to the map of blocks with the new key.
          myBlocks.Clear(false);
          mypLastBlock = myBlocks.Bound(aNewKey, Block(aNewAddress, myBlockSize));
        }
      }
    }
  }
}

//=======================================================================
// function : findBlock
// purpose  : Find a block that the given allocation unit belongs to
//=======================================================================
NCollection_AccAllocator::Block* NCollection_AccAllocator::findBlock(void* const theAddress,
                                                                     Key&        theKey) noexcept
{
  theKey = getKey(theAddress);

  Block* aBlock = myBlocks.ChangeSeek(theKey);
  if (aBlock && aBlock->address <= theAddress)
  {
    return aBlock;
  }

  theKey.Value--;
  aBlock = myBlocks.ChangeSeek(theKey);
  if (aBlock && (uint8_t*)aBlock->address + (size_t)myBlockSize > theAddress)
  {
    return aBlock;
  }

  return nullptr;
}

//=======================================================================
// function : allocateNewBlock
// purpose  : Allocate a new block and return a pointer to it
//=======================================================================
NCollection_AccAllocator::Block* NCollection_AccAllocator::allocateNewBlock(const size_t theSize)
{
  const size_t aRoundSize = (theSize + 3) & ~0x3;
  void*        anAddress  = Standard::Allocate(aRoundSize);
  // we depend on the fact that Standard::Allocate always returns
  // a pointer aligned to a 4 byte boundary
  mypLastBlock = myBlocks.Bound(getKey(anAddress), Block(anAddress, theSize, mypLastBlock));
#ifdef OCCT_DEBUG_FINDBLOCK
  Key aKey;
  Standard_ASSERT_VOID(mypLastBlock == findBlock((uint8_t*)mypLastBlock->allocStart - 1, aKey),
                       "improper work of NCollection_AccAllocator::findBlock");
#endif
  return mypLastBlock;
}
