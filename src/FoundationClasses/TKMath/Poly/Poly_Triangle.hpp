#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OutOfRange.hpp>

class Poly_Triangle
{
public:
  DEFINE_STANDARD_ALLOC

  Poly_Triangle() { myNodes[0] = myNodes[1] = myNodes[2] = 0; }

  Poly_Triangle(const int theN1, const int theN2, const int theN3)
  {
    myNodes[0] = theN1;
    myNodes[1] = theN2;
    myNodes[2] = theN3;
  }

  void Set(const int theN1, const int theN2, const int theN3)
  {
    myNodes[0] = theN1;
    myNodes[1] = theN2;
    myNodes[2] = theN3;
  }

  void Set(const int theIndex, const int theNode)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 3,
                                 "Poly_Triangle::Set(), invalid index");
    myNodes[theIndex - 1] = theNode;
  }

  void Get(int& theN1, int& theN2, int& theN3) const
  {
    theN1 = myNodes[0];
    theN2 = myNodes[1];
    theN3 = myNodes[2];
  }

  int Value(const int theIndex) const
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 3,
                                 "Poly_Triangle::Value(), invalid index");
    return myNodes[theIndex - 1];
  }

  int operator()(const int Index) const { return Value(Index); }

  int& ChangeValue(const int theIndex)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 3,
                                 "Poly_Triangle::ChangeValue(), invalid index");
    return myNodes[theIndex - 1];
  }

  int& operator()(const int Index) { return ChangeValue(Index); }

protected:
  int myNodes[3];
};
