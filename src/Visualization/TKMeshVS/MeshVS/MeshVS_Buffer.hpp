#pragma once

#include <Standard.hpp>
#include <gp_Pnt.hpp>

/**
 * General purpose buffer that is allocated on the stack with a
 * constant size MeshVS_BufSize, or is allocated dynamically if the requested
 * size exceeds the standard one.
 * It is useful when an allocation of an array of unknown size is needed,
 * and most often the array is small enough to allocate as automatic C array.
 */

//! define the constant to the size of 10 points
#define MeshVS_BufSize 10 * 3 * sizeof(double)

class MeshVS_Buffer
{
public:
  //! Constructor of the buffer of the requested size
  MeshVS_Buffer(const size_t theSize)
      : myDynData(nullptr)
  {
    if (theSize > MeshVS_BufSize)
      myDynData = Standard::Allocate(theSize);
  }

  //! Destructor
  ~MeshVS_Buffer()
  {
    if (myDynData)
    {
      Standard::Free(myDynData);
      myDynData = nullptr;
    }
  }

  //! Cast the buffer to the void pointer
  operator void*() { return myDynData ? myDynData : (void*)myAutoData; }

  //! Interpret the buffer as a reference to double
  operator double&() { return *(myDynData ? (double*)myDynData : (double*)myAutoData); }

  //! Interpret the buffer as a reference to int
  operator int&() { return *(myDynData ? (int*)myDynData : (int*)myAutoData); }

  //! Interpret the buffer as a reference to gp_Pnt
  operator gp_Pnt&() { return *(myDynData ? (gp_Pnt*)myDynData : (gp_Pnt*)myAutoData); }

private:
  //! Deprecate copy constructor
  MeshVS_Buffer(const MeshVS_Buffer&) {}

  //! Deprecate copy operation
  MeshVS_Buffer& operator=(const MeshVS_Buffer&) { return *this; }

  char  myAutoData[MeshVS_BufSize];
  void* myDynData;
};
