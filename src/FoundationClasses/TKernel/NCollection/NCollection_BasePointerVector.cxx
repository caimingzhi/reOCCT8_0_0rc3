

#include <NCollection_BasePointerVector.hpp>

#include <cstring>

NCollection_BasePointerVector::NCollection_BasePointerVector(
  const NCollection_BasePointerVector& theOther)
    : mySize(theOther.mySize),
      myCapacity(theOther.myCapacity)
{
  if (myCapacity > 0)
  {
    myArray = myAllocator.allocate(myCapacity);
    memcpy(myArray, theOther.myArray, Size() * sizeof(void*));
  }
}

NCollection_BasePointerVector::NCollection_BasePointerVector(
  NCollection_BasePointerVector&& theOther) noexcept
    : mySize(theOther.mySize),
      myCapacity(theOther.myCapacity),
      myArray(theOther.myArray)
{
  theOther.myCapacity = 0;
  theOther.mySize     = 0;
  theOther.myArray    = nullptr;
}

void NCollection_BasePointerVector::Append(const void* thePnt)
{
  if (mySize == myCapacity)
  {
    if (myCapacity == 0)
    {
      myCapacity = 8;
    }
    else
    {
      myCapacity <<= 1;
    }
    myArray = myAllocator.reallocate(myArray, myCapacity);
  }
  myArray[mySize++] = (void*)thePnt;
}

void NCollection_BasePointerVector::SetValue(const size_t theInd, const void* thePnt)
{
  if (theInd >= myCapacity)
  {
    if (myCapacity == 0)
    {
      myCapacity = 8;
    }
    while (myCapacity < theInd)
    {
      myCapacity <<= 1;
    }
    myArray = myAllocator.reallocate(myArray, myCapacity);
    memset(myArray + mySize, 0, (theInd - mySize) * sizeof(void**));
    mySize = theInd;
  }
  myArray[theInd] = (void*)thePnt;
}

void NCollection_BasePointerVector::clear()
{
  if (myCapacity > 0)
  {
    myAllocator.deallocate(myArray, myCapacity);
  }
  myArray    = nullptr;
  myCapacity = 0;
}

NCollection_BasePointerVector& NCollection_BasePointerVector::operator=(
  const NCollection_BasePointerVector& theOther)
{
  if (this == &theOther)
  {
    return *this;
  }
  mySize = theOther.mySize;
  if (myCapacity < theOther.myCapacity)
  {
    clear();
    myCapacity = theOther.myCapacity;
    myArray    = myAllocator.allocate(myCapacity);
  }
  memcpy(myArray, theOther.myArray, mySize * sizeof(void*));
  return *this;
}

NCollection_BasePointerVector& NCollection_BasePointerVector::operator=(
  NCollection_BasePointerVector&& theOther) noexcept
{
  if (this == &theOther)
  {
    return *this;
  }
  clear();
  mySize              = theOther.mySize;
  myCapacity          = theOther.myCapacity;
  myArray             = theOther.myArray;
  theOther.myCapacity = 0;
  theOther.mySize     = 0;
  theOther.myArray    = nullptr;
  return *this;
}
