#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>

class HLRAlgo_PolyHidingData
{
public:
  DEFINE_STANDARD_ALLOC

  struct TriangleIndices
  {
    int Index, Min, Max;
  };

  struct PlaneT
  {
    PlaneT()
        : D(0.0)
    {
    }

    gp_XYZ Normal;
    double D;
  };

  HLRAlgo_PolyHidingData() = default;

  void Set(const int    Index,
           const int    Minim,
           const int    Maxim,
           const double A,
           const double B,
           const double C,
           const double D)
  {
    myIndices.Index = Index;
    myIndices.Min   = Minim;
    myIndices.Max   = Maxim;
    myPlane.Normal  = gp_XYZ(A, B, C);
    myPlane.D       = D;
  }

  TriangleIndices& Indices() { return myIndices; }

  PlaneT& Plane() { return myPlane; }

private:
  TriangleIndices myIndices;
  PlaneT          myPlane;
};
