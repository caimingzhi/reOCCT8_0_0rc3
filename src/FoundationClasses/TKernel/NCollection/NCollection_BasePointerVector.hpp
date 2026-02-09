#pragma once

#include <Standard.hpp>

#include <NCollection_Allocator.hpp>
#include <NCollection_DefineAlloc.hpp>

class NCollection_BasePointerVector
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

public:
  NCollection_BasePointerVector() noexcept = default;

  Standard_EXPORT NCollection_BasePointerVector(const NCollection_BasePointerVector& theOther);

  Standard_EXPORT NCollection_BasePointerVector(NCollection_BasePointerVector&& theOther) noexcept;

  ~NCollection_BasePointerVector() { clear(); }

  bool IsEmpty() const noexcept { return mySize == 0; }

  size_t Size() const noexcept { return mySize; }

  size_t Capacity() const noexcept { return myCapacity; }

  void RemoveLast() noexcept { mySize--; }

  void Clear(const bool theReleaseMemory = false)
  {
    if (theReleaseMemory)
      clear();
    mySize = 0;
  }

public:
  void** GetArray() const noexcept { return myArray; }

  void* Value(const size_t theInd) const noexcept { return myArray[theInd]; }

public:
  Standard_EXPORT void Append(const void* thePnt);

  Standard_EXPORT void SetValue(const size_t theInd, const void* thePnt);

  Standard_EXPORT NCollection_BasePointerVector& operator=(
    const NCollection_BasePointerVector& theOther);

  Standard_EXPORT NCollection_BasePointerVector& operator=(
    NCollection_BasePointerVector&& theOther) noexcept;

private:
  Standard_EXPORT void clear();

private:
  size_t                       mySize     = 0;
  size_t                       myCapacity = 0;
  void**                       myArray    = nullptr;
  NCollection_Allocator<void*> myAllocator;
};
