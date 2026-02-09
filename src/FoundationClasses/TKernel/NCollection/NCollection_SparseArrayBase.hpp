#pragma once

#include <Standard.hpp>
#include <Standard_TypeDef.hpp>
#include <Standard_OutOfRange.hpp>

class NCollection_SparseArrayBase
{
public:
  Standard_EXPORT void Clear();

  size_t Size() const noexcept { return mySize; }

  Standard_EXPORT bool HasValue(const size_t theIndex) const;

  Standard_EXPORT bool UnsetValue(const size_t theIndex);

#if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530)
public:
#else
private:
#endif

  class Block
  {
  public:
    typedef unsigned char Cell;

    static constexpr size_t BitsPerCell() noexcept { return sizeof(Cell) * 8; }

  public:
    Block(void* const theAddr, const size_t theNbItems, const size_t theItemSize)
        : Count((size_t*)theAddr),
          Array((char*)theAddr + sizeof(size_t)),
          Bits((Cell*)((char*)theAddr + sizeof(size_t) + theNbItems * theItemSize))
    {
    }

    static constexpr size_t Size(const size_t theNbItems, const size_t theItemSize) noexcept
    {
      return sizeof(size_t) + sizeof(Cell) * ((theNbItems + BitsPerCell() - 1) / BitsPerCell())
             + theNbItems * theItemSize;
    }

    static char* ToArray(void* const theAddress, const size_t, const size_t) noexcept
    {
      return (char*)theAddress + sizeof(size_t);
    }

  public:
    Cell Set(size_t i) noexcept
    {
      Cell* abyte = Bits + i / BitsPerCell();
      Cell  amask = (Cell)('\1' << (i % BitsPerCell()));
      Cell  anold = (Cell)(*abyte & amask);
      *abyte      = (Cell)(*abyte | amask);
      return !anold;
    }

    Cell IsSet(size_t i) noexcept
    {
      Cell* abyte = Bits + i / BitsPerCell();
      Cell  amask = (Cell)('\1' << (i % BitsPerCell()));
      return (Cell)(*abyte & amask);
    }

    Cell Unset(size_t i) noexcept
    {
      Cell* abyte = Bits + i / BitsPerCell();
      Cell  amask = (Cell)('\1' << (i % BitsPerCell()));
      Cell  anold = (Cell)(*abyte & amask);
      *abyte      = (Cell)(*abyte & ~amask);
      return anold;
    }

  public:
    size_t* Count;
    void*   Array;
    Cell*   Bits;
  };

public:
  class Iterator
  {
  public:
    void Restart() { init(myArr); }

    bool More() const noexcept { return myHasMore; }

    Standard_EXPORT void Next();

    size_t Index() const noexcept { return myIBlock * myArr->myBlockSize + myInd; }

  protected:
    Standard_EXPORT Iterator(const NCollection_SparseArrayBase* theArray = nullptr);

    Standard_EXPORT void init(const NCollection_SparseArrayBase* theArray);

    void* value() const noexcept { return myArr->getItem(myBlock, myInd); }

  private:
    const NCollection_SparseArrayBase* myArr;
    bool                               myHasMore;
    size_t                             myIBlock;
    size_t                             myInd;
    Block                              myBlock;
  };
  friend class Iterator;

private:
  NCollection_SparseArrayBase(const NCollection_SparseArrayBase&)            = delete;
  NCollection_SparseArrayBase& operator=(const NCollection_SparseArrayBase&) = delete;

protected:
  NCollection_SparseArrayBase(size_t theItemSize, size_t theBlockSize) noexcept
      : myItemSize(theItemSize),
        myBlockSize(theBlockSize),
        myNbBlocks(0),
        mySize(0),
        myData(nullptr)
  {
  }

  virtual ~NCollection_SparseArrayBase() { Clear(); }

protected:
  Block getBlock(void* const theAddr) const noexcept
  {
    return Block(theAddr, myBlockSize, myItemSize);
  }

  void* getItem(const Block& theBlock, size_t theInd) const noexcept
  {
    return ((char*)theBlock.Array) + myItemSize * theInd;
  }

  void* getValue(const size_t theIndex) const
  {
    Standard_OutOfRange_Raise_if(
      !HasValue(theIndex),
      "NCollection_SparseArray::Value()") return Block::ToArray(myData[theIndex / myBlockSize],
                                                                myBlockSize,
                                                                myItemSize)
      + myItemSize * (theIndex % myBlockSize);
  }

  Standard_EXPORT void* setValue(const size_t theIndex, void* const theValue);

  Standard_EXPORT void assign(const NCollection_SparseArrayBase& theOther);

  Standard_EXPORT void exchange(NCollection_SparseArrayBase& theOther) noexcept;

protected:
  virtual void createItem(void* theAddress, void* theOther) = 0;

  virtual void destroyItem(void* theAddress) = 0;

  virtual void copyItem(void* theAddress, void* theOther) = 0;

private:
  void allocData(const size_t iBlock);

  void freeBlock(const size_t iBlock);

protected:
  size_t myItemSize;
  size_t myBlockSize;
  size_t myNbBlocks;
  size_t mySize;
  void** myData;
};
