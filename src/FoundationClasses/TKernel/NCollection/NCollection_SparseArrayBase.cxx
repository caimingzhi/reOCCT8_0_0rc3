#include <NCollection_SparseArrayBase.hpp>
#include <Standard_ProgramError.hpp>
#include <Standard.hpp>

#include <algorithm>
#include <cstring>

void NCollection_SparseArrayBase::allocData(const size_t iBlock)
{
  if (iBlock < myNbBlocks)
    return;

  size_t newNbBlocks = (myNbBlocks ? myNbBlocks * 2 : myBlockSize);
  while (iBlock >= newNbBlocks)
    newNbBlocks *= 2;

  void** newData = (void**)Standard::AllocateOptimal(newNbBlocks * sizeof(void*));
  if (myNbBlocks > 0)
    memcpy(newData, myData, myNbBlocks * sizeof(void*));
  memset(newData + myNbBlocks, 0, (newNbBlocks - myNbBlocks) * sizeof(void*));

  Standard::Free(myData);
  myData     = newData;
  myNbBlocks = newNbBlocks;
}

void NCollection_SparseArrayBase::freeBlock(const size_t iBlock)
{
  void*& anAddr = myData[iBlock];
  if (!anAddr)
    return;

  Block aBlock = getBlock(anAddr);

  for (size_t anInd = 0; anInd < myBlockSize; anInd++)
  {
    if (aBlock.IsSet(anInd))
    {
      destroyItem(getItem(aBlock, anInd));
      mySize--;
    }
  }
  Standard::Free(anAddr);
  anAddr = nullptr;
}

void NCollection_SparseArrayBase::Clear()
{

  for (size_t iBlock = 0; iBlock < myNbBlocks; iBlock++)
  {
    if (myData[iBlock])
    {
      freeBlock(iBlock);
    }
  }

  Standard::Free(myData);
  myData     = nullptr;
  myNbBlocks = 0;
  mySize     = 0;

  Standard_ProgramError_Raise_if(
    mySize != 0,
    "NCollection_SparseArrayBase: Implementation error: inconsistent items count")
}

void NCollection_SparseArrayBase::assign(const NCollection_SparseArrayBase& theOther)
{
  if (this == &theOther)
    return;

  if (myBlockSize != theOther.myBlockSize)
    Clear();
  myBlockSize = theOther.myBlockSize;

  size_t iBlock = 0;
  for (; iBlock < theOther.myNbBlocks; iBlock++)
  {
    if (!theOther.myData[iBlock])
    {

      if (iBlock < myNbBlocks && myData[iBlock])
        freeBlock(iBlock);
      continue;
    }

    if (iBlock >= myNbBlocks)
      allocData(iBlock);
    Block anOtherBlock = getBlock(theOther.myData[iBlock]);

    void*& anAddr = myData[iBlock];
    if (!anAddr)
    {
      const size_t aBlockSize = Block::Size(myBlockSize, myItemSize);
      anAddr                  = Standard::AllocateOptimal(aBlockSize);
      memset(anAddr, 0, aBlockSize);
      Block aBlock(getBlock(anAddr));
      for (size_t anInd = 0; anInd < myBlockSize; anInd++)
        if (anOtherBlock.IsSet(anInd))
        {
          void* anItem = getItem(aBlock, anInd);
          aBlock.Set(anInd);
          (*aBlock.Count)++;
          mySize++;
          createItem(anItem, getItem(anOtherBlock, anInd));
        }
    }

    else
    {
      Block aBlock(getBlock(anAddr));
      for (size_t anInd = 0; anInd < myBlockSize; anInd++)
      {
        void* anItem = getItem(aBlock, anInd);
        if (anOtherBlock.IsSet(anInd))
        {
          void* anOtherItem = getItem(anOtherBlock, anInd);
          if (aBlock.IsSet(anInd))
          {
            copyItem(anItem, anOtherItem);
          }
          else
          {
            aBlock.Set(anInd);
            (*aBlock.Count)++;
            mySize++;
            createItem(anItem, getItem(anOtherBlock, anInd));
          }
        }
        else if (aBlock.IsSet(anInd))
        {
          aBlock.Set(anInd);
          (*aBlock.Count)--;
          mySize--;
          destroyItem(anItem);
        }
      }
    }
  }

  for (; iBlock < myNbBlocks; iBlock++)
    if (myData[iBlock])
      freeBlock(iBlock);

  Standard_ProgramError_Raise_if(
    mySize != theOther.mySize,
    "NCollection_SparseArrayBase: Implementation error: inconsistent items count")
}

void NCollection_SparseArrayBase::exchange(NCollection_SparseArrayBase& theOther) noexcept
{
  if (this == &theOther)
    return;

  std::swap(myItemSize, theOther.myItemSize);
  std::swap(myBlockSize, theOther.myBlockSize);
  std::swap(myNbBlocks, theOther.myNbBlocks);
  std::swap(mySize, theOther.mySize);
  std::swap(myData, theOther.myData);
}

void* NCollection_SparseArrayBase::setValue(const size_t theIndex, void* const theValue)
{
  size_t iBlock = theIndex / myBlockSize;

  if (iBlock >= myNbBlocks)
    allocData(iBlock);

  void*& anAddr = myData[iBlock];
  if (!anAddr)
  {
    const size_t aBlockSize = Block::Size(myBlockSize, myItemSize);
    anAddr                  = Standard::AllocateOptimal(aBlockSize);
    memset(anAddr, 0, aBlockSize);
  }

  Block  aBlock(getBlock(anAddr));
  size_t anInd  = theIndex % myBlockSize;
  void*  anItem = getItem(aBlock, anInd);

  if (aBlock.Set(anInd))
  {
    (*aBlock.Count)++;
    mySize++;
    createItem(anItem, theValue);
  }
  else
  {

    copyItem(anItem, theValue);
  }

  return anItem;
}

bool NCollection_SparseArrayBase::HasValue(const size_t theIndex) const
{
  size_t iBlock = theIndex / myBlockSize;
  if (iBlock >= myNbBlocks || !myData[iBlock])
    return false;
  return getBlock(myData[iBlock]).IsSet(theIndex % myBlockSize) != 0;
}

bool NCollection_SparseArrayBase::UnsetValue(const size_t theIndex)
{

  size_t iBlock = theIndex / myBlockSize;
  if (iBlock >= myNbBlocks || !myData[iBlock])
    return false;

  Block  aBlock(getBlock(myData[iBlock]));
  size_t anInd = theIndex % myBlockSize;
  if (!aBlock.Unset(anInd))
    return false;

  destroyItem(getItem(aBlock, anInd));
  (*aBlock.Count)--;
  mySize--;

  if (!(*aBlock.Count))
    freeBlock(iBlock);

  return true;
}

NCollection_SparseArrayBase::Iterator::Iterator(const NCollection_SparseArrayBase* theArray)
    : myArr((NCollection_SparseArrayBase*)theArray),
      myHasMore(false),
      myIBlock(0),
      myInd(0),
      myBlock(nullptr, 0, 0)
{
  init(theArray);
}

void NCollection_SparseArrayBase::Iterator::Next()
{
  if (!myArr || !myHasMore)
    return;

  for (myInd++;; myInd++)
  {

    if (myInd >= myArr->myBlockSize)
    {
      for (myIBlock++;; myIBlock++)
      {
        if (myIBlock >= myArr->myNbBlocks)
        {
          myHasMore = false;
          return;
        }
        if (myArr->myData[myIBlock])
        {
          myInd   = 0;
          myBlock = Block(myArr->myData[myIBlock], myArr->myBlockSize, myArr->myItemSize);
          break;
        }
      }
    }

    if (myBlock.IsSet(myInd))
      return;
  }
}

void NCollection_SparseArrayBase::Iterator::init(const NCollection_SparseArrayBase* theArray)
{
  myArr     = (NCollection_SparseArrayBase*)theArray;
  myHasMore = false;
  if (myArr)
  {
    myInd = 0;

    for (myIBlock = 0; myIBlock < myArr->myNbBlocks; myIBlock++)
    {
      if (!myArr->myData[myIBlock])
        continue;
      myHasMore = true;
      myBlock   = Block(myArr->myData[myIBlock], myArr->myBlockSize, myArr->myItemSize);

      if (!myBlock.IsSet(myInd))
        Next();
      return;
    }
  }
}
