#pragma once

#include <NCollection_Vector.hpp>
#include <stdio.h>

template <class Type>
class IntPolyh_Array
{
public:
  typedef NCollection_Vector<Type> IntPolyh_VectorOfType;

  IntPolyh_Array(const int aIncrement = 256)
  {
    myNbAllocated = 0;
    myNbItems     = 0;
    myIncrement   = aIncrement;
  }

  IntPolyh_Array(const int aN, const int aIncrement = 256)
  {
    myNbItems   = 0;
    myIncrement = aIncrement;
    Init(aN);
  }

  IntPolyh_Array& operator=(const IntPolyh_Array& aOther) { return Copy(aOther); }

  IntPolyh_Array& Copy(const IntPolyh_Array& aOther)
  {
    myVectorOfType.Clear();
    Init(aOther.myNbAllocated);
    myVectorOfType = aOther.myVectorOfType;
    myNbItems      = aOther.myNbItems;

    return *this;
  }

  void Init(const int aN)
  {
    Type aSL;

    myVectorOfType.SetValue(aN, aSL);
    myNbAllocated = aN;
  }

  void IncrementNbItems()
  {
    myNbItems++;
    if (myNbItems >= myNbAllocated)
    {
      int aN;

      aN = myNbAllocated + myIncrement;
      Init(aN);
    }
  }

  int GetN() const { return myNbAllocated; }

  int NbItems() const { return myNbItems; }

  void SetNbItems(const int aNb) { myNbItems = aNb; }

  const Type& Value(const int aIndex) const { return myVectorOfType.Value(aIndex); }

  const Type& operator[](const int aIndex) const { return Value(aIndex); }

  Type& ChangeValue(const int aIndex) { return myVectorOfType.ChangeValue(aIndex); }

  Type& operator[](const int aIndex) { return ChangeValue(aIndex); }

  void Dump() const
  {
    printf("\n ArrayOfSectionLines 0-> %d", myNbItems - 1);
    for (int i = 0; i < myNbItems; i++)
    {
      (*this)[i].Dump();
    }
    printf("\n");
  }

protected:
  int                   myNbAllocated;
  int                   myNbItems;
  int                   myIncrement;
  IntPolyh_VectorOfType myVectorOfType;
};
