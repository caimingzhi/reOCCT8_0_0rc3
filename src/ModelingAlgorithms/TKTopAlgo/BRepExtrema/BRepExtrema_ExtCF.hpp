#pragma once

#include <Extrema_ExtCS.hpp>
#include <NCollection_Sequence.hpp>
#include <Extrema_POnSurf.hpp>
#include <Extrema_POnCurv.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <Standard_DefineAlloc.hpp>

class TopoDS_Edge;
class TopoDS_Face;

class BRepExtrema_ExtCF
{
public:
  DEFINE_STANDARD_ALLOC

  BRepExtrema_ExtCF() = default;

  Standard_EXPORT BRepExtrema_ExtCF(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT void Initialize(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT void Perform(const TopoDS_Edge& E, const TopoDS_Face& F);

  bool IsDone() const { return myExtCS.IsDone(); }

  int NbExt() const { return mySqDist.Length(); }

  double SquareDistance(const int N) const { return mySqDist.Value(N); }

  bool IsParallel() const { return myExtCS.IsParallel(); }

  double ParameterOnEdge(const int N) const { return myPointsOnC.Value(N).Parameter(); }

  void ParameterOnFace(const int N, double& U, double& V) const
  {
    myPointsOnS.Value(N).Parameter(U, V);
  }

  gp_Pnt PointOnEdge(const int N) const { return myPointsOnC.Value(N).Value(); }

  gp_Pnt PointOnFace(const int N) const { return myPointsOnS.Value(N).Value(); }

private:
  Extrema_ExtCS                         myExtCS;
  NCollection_Sequence<double>          mySqDist;
  NCollection_Sequence<Extrema_POnSurf> myPointsOnS;
  NCollection_Sequence<Extrema_POnCurv> myPointsOnC;
  occ::handle<BRepAdaptor_Surface>      myHS;
};
