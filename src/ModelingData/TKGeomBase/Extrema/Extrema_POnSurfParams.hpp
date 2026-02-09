#pragma once

enum Extrema_ElementType
{
  Extrema_Node,
  Extrema_UIsoEdge,
  Extrema_VIsoEdge,
  Extrema_Face
};

#include <Extrema_POnSurf.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class gp_Pnt;

class Extrema_POnSurfParams : public Extrema_POnSurf
{
public:
  DEFINE_STANDARD_ALLOC

  Extrema_POnSurfParams()
      : mySqrDistance(0.),
        myElementType(Extrema_Node),
        myIndexU(0),
        myIndexV(0)
  {
  }

  Extrema_POnSurfParams(const double theU, const double theV, const gp_Pnt& thePnt)
      : Extrema_POnSurf(theU, theV, thePnt),
        mySqrDistance(0.),
        myElementType(Extrema_Node),
        myIndexU(0),
        myIndexV(0)
  {
  }

  void SetSqrDistance(const double theSqrDistance) { mySqrDistance = theSqrDistance; }

  double GetSqrDistance() const { return mySqrDistance; }

  void SetElementType(const Extrema_ElementType theElementType) { myElementType = theElementType; }

  Extrema_ElementType GetElementType() const { return myElementType; }

  void SetIndices(const int theIndexU, const int theIndexV)
  {
    myIndexU = theIndexU;
    myIndexV = theIndexV;
  }

  void GetIndices(int& theIndexU, int& theIndexV) const
  {
    theIndexU = myIndexU;
    theIndexV = myIndexV;
  }

private:
  double              mySqrDistance;
  Extrema_ElementType myElementType;
  int                 myIndexU;
  int                 myIndexV;
};
