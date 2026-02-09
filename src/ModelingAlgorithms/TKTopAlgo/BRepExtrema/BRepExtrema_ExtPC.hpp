#pragma once

#include <Extrema_ExtPC.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <Standard_DefineAlloc.hpp>

class TopoDS_Vertex;
class TopoDS_Edge;

class BRepExtrema_ExtPC
{
public:
  DEFINE_STANDARD_ALLOC

  BRepExtrema_ExtPC() = default;

  Standard_EXPORT BRepExtrema_ExtPC(const TopoDS_Vertex& V, const TopoDS_Edge& E);

  Standard_EXPORT void Initialize(const TopoDS_Edge& E);

  Standard_EXPORT void Perform(const TopoDS_Vertex& V);

  bool IsDone() const { return myExtPC.IsDone(); }

  int NbExt() const { return myExtPC.NbExt(); }

  bool IsMin(const int N) const { return myExtPC.IsMin(N); }

  double SquareDistance(const int N) const { return myExtPC.SquareDistance(N); }

  double Parameter(const int N) const { return myExtPC.Point(N).Parameter(); }

  gp_Pnt Point(const int N) const { return myExtPC.Point(N).Value(); }

  void TrimmedSquareDistances(double& dist1, double& dist2, gp_Pnt& pnt1, gp_Pnt& pnt2) const
  {
    myExtPC.TrimmedSquareDistances(dist1, dist2, pnt1, pnt2);
  }

private:
  Extrema_ExtPC                  myExtPC;
  occ::handle<BRepAdaptor_Curve> myHC;
};
