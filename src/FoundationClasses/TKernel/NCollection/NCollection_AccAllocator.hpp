#pragma once

#include <NCollection_BaseAllocator.hpp>
#include <NCollection_DataMap.hpp>

class NCollection_AccAllocator : public NCollection_BaseAllocator
{

public:
  static constexpr size_t Align = 4;

  static constexpr size_t DefaultBlockSize = 24600;

  static constexpr int MaxLookupBlocks = 16;

public:
  Standard_EXPORT NCollection_AccAllocator(const size_t theBlockSize = DefaultBlockSize);

  Standard_EXPORT ~NCollection_AccAllocator() override;

  Standard_EXPORT void* Allocate(const size_t theSize) override;

  void* AllocateOptimal(const size_t theSize) override { return Allocate(theSize); }

  Standard_EXPORT void Free(void* theAddress) override;

protected:
  class AlignedSize
  {
    size_t myValue;

  public:
    constexpr AlignedSize() noexcept
        : myValue(0)
    {
    }

    constexpr AlignedSize(const size_t theValue) noexcept
        : myValue((theValue + Align - 1) & ~(Align - 1))
    {
    }

    constexpr operator size_t() const noexcept { return myValue; }
  };

  class AlignedPtr
  {
    uint8_t* myValue;

  public:
    constexpr AlignedPtr() noexcept
        : myValue(nullptr)
    {
    }

    AlignedPtr(void* const theValue) noexcept
        : myValue((uint8_t*)((size_t)theValue & ~(Align - 1)))
    {
    }

    operator void*() const noexcept { return myValue; }

    operator uint8_t*() const noexcept { return myValue; }

    AlignedPtr operator-(const AlignedSize theValue) const noexcept { return myValue - theValue; }

    AlignedPtr operator+(const AlignedSize theValue) const noexcept { return myValue + theValue; }

    AlignedPtr operator-=(const AlignedSize theValue) noexcept { return myValue -= theValue; }

    AlignedPtr operator+=(const AlignedSize theValue) noexcept { return myValue += theValue; }
  };

  struct Key
  {
    size_t Value;
  };

  class Hasher
  {
  public:
    size_t operator()(const Key theKey) const noexcept { return theKey.Value; }

    bool operator()(const Key theKey1, const Key theKey2) const noexcept
    {
      return theKey1.Value == theKey2.Value;
    }
  };

  struct Block
  {
    void*      address;
    AlignedPtr allocStart;
    Block*     prevBlock;
    int        allocCount;

    Block(void* const theAddress, const size_t theSize, Block* thePrevBlock = nullptr) noexcept
        : address(theAddress),
          prevBlock(thePrevBlock),
          allocCount(0)
    {
      SetFreeSize(theSize);
    }

    void SetFreeSize(const size_t theSize) noexcept { allocStart = (uint8_t*)address + theSize; }

    size_t FreeSize() const noexcept { return (uint8_t*)allocStart - (uint8_t*)address; }

    AlignedPtr Allocate(const AlignedSize theSize) noexcept
    {
      allocCount++;
      return allocStart -= theSize;
    }

    void Free() { allocCount--; }

    bool IsEmpty() const noexcept { return allocCount == 0; }
  };

protected:
  inline Key getKey(void* const theAddress) const noexcept
  {
    Key aKey = {(size_t)theAddress / myBlockSize};
    return aKey;
  }

  Standard_EXPORT Block* findBlock(void* const theAddress, Key& theKey) noexcept;

  Standard_EXPORT Block* allocateNewBlock(const size_t theSize);

private:
  NCollection_AccAllocator(const NCollection_AccAllocator&)            = delete;
  NCollection_AccAllocator& operator=(const NCollection_AccAllocator&) = delete;

protected:
  AlignedSize                             myBlockSize;
  Block*                                  mypLastBlock;
  NCollection_DataMap<Key, Block, Hasher> myBlocks;

public:
  DEFINE_STANDARD_RTTIEXT(NCollection_AccAllocator, NCollection_BaseAllocator)
};
