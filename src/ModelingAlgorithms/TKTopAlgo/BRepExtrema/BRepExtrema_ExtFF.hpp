#pragma once

#include <Extrema_ExtSS.hpp>
#include <NCollection_Sequence.hpp>
#include <Extrema_POnSurf.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <Standard_DefineAlloc.hpp>

class TopoDS_Face;

class BRepExtrema_ExtFF
{
public:
  DEFINE_STANDARD_ALLOC

  BRepExtrema_ExtFF() = default;

  Standard_EXPORT BRepExtrema_ExtFF(const TopoDS_Face& F1, const TopoDS_Face& F2);

  Standard_EXPORT void Initialize(const TopoDS_Face& F2);

  Standard_EXPORT void Perform(const TopoDS_Face& F1, const TopoDS_Face& F2);

  bool IsDone() const { return myExtSS.IsDone(); }

  bool IsParallel() const { return myExtSS.IsParallel(); }

  int NbExt() const { return mySqDist.Length(); }

  double SquareDistance(const int N) const { return mySqDist.Value(N); }

  void ParameterOnFace1(const int N, double& U, double& V) const
  {
    myPointsOnS1.Value(N).Parameter(U, V);
  }

  void ParameterOnFace2(const int N, double& U, double& V) const
  {
    myPointsOnS2.Value(N).Parameter(U, V);
  }

  gp_Pnt PointOnFace1(const int N) const { return myPointsOnS1.Value(N).Value(); }

  gp_Pnt PointOnFace2(const int N) const { return myPointsOnS2.Value(N).Value(); }

private:
  Extrema_ExtSS                         myExtSS;
  NCollection_Sequence<double>          mySqDist;
  NCollection_Sequence<Extrema_POnSurf> myPointsOnS1;
  NCollection_Sequence<Extrema_POnSurf> myPointsOnS2;
  occ::handle<BRepAdaptor_Surface>      myHS;
};
