#pragma once

#include <Standard.hpp>
#include <gp_Pnt.hpp>

#define MeshVS_BufSize 10 * 3 * sizeof(double)

class MeshVS_Buffer
{
public:
  MeshVS_Buffer(const size_t theSize)
      : myDynData(nullptr)
  {
    if (theSize > MeshVS_BufSize)
      myDynData = Standard::Allocate(theSize);
  }

  ~MeshVS_Buffer()
  {
    if (myDynData)
    {
      Standard::Free(myDynData);
      myDynData = nullptr;
    }
  }

  operator void*() { return myDynData ? myDynData : (void*)myAutoData; }

  operator double&() { return *(myDynData ? (double*)myDynData : (double*)myAutoData); }

  operator int&() { return *(myDynData ? (int*)myDynData : (int*)myAutoData); }

  operator gp_Pnt&() { return *(myDynData ? (gp_Pnt*)myDynData : (gp_Pnt*)myAutoData); }

private:
  MeshVS_Buffer(const MeshVS_Buffer&) {}

  MeshVS_Buffer& operator=(const MeshVS_Buffer&) { return *this; }

  char  myAutoData[MeshVS_BufSize];
  void* myDynData;
};
