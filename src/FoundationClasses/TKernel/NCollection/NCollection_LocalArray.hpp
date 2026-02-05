#pragma once

#include <Standard.hpp>
#include <Standard_TypeDef.hpp>

//! Auxiliary class optimizing creation of array buffer
//! (using stack allocation for small arrays).
template <class theItem, int MAX_ARRAY_SIZE = 1024>
class NCollection_LocalArray
{
public:
  explicit NCollection_LocalArray(const size_t theSize)
      : myPtr(myBuffer)
  {
    Allocate(theSize);
  }

  NCollection_LocalArray() noexcept
      : myPtr(myBuffer),
        mySize(0)
  {
  }

  ~NCollection_LocalArray() { Deallocate(); }

  void Allocate(const size_t theSize)
  {
    Deallocate();
    if (theSize > MAX_ARRAY_SIZE)
      myPtr = (theItem*)Standard::Allocate(theSize * sizeof(theItem));
    else
      myPtr = myBuffer;

    mySize = theSize;
  }

  size_t Size() const noexcept { return mySize; }

  operator theItem*() const noexcept { return myPtr; }

private:
  NCollection_LocalArray(const NCollection_LocalArray&)            = delete;
  NCollection_LocalArray& operator=(const NCollection_LocalArray&) = delete;

protected:
  void Deallocate()
  {
    if (myPtr != myBuffer)
      Standard::Free(myPtr);
  }

protected:
  theItem  myBuffer[MAX_ARRAY_SIZE];
  theItem* myPtr;
  size_t   mySize;
};
