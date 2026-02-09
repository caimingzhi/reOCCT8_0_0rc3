#pragma once

#include <Extrema_ExtCC.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <Standard_DefineAlloc.hpp>

class TopoDS_Edge;
class gp_Pnt;

class BRepExtrema_ExtCC
{
public:
  DEFINE_STANDARD_ALLOC

  BRepExtrema_ExtCC() = default;

  Standard_EXPORT BRepExtrema_ExtCC(const TopoDS_Edge& E1, const TopoDS_Edge& E2);

  Standard_EXPORT void Initialize(const TopoDS_Edge& E2);

  Standard_EXPORT void Perform(const TopoDS_Edge& E1);

  bool IsDone() const { return myExtCC.IsDone(); }

  int NbExt() const { return myExtCC.NbExt(); }

  bool IsParallel() const { return myExtCC.IsParallel(); }

  double SquareDistance(const int N) const { return myExtCC.SquareDistance(N); }

  Standard_EXPORT double ParameterOnE1(const int N) const;

  Standard_EXPORT gp_Pnt PointOnE1(const int N) const;

  Standard_EXPORT double ParameterOnE2(const int N) const;

  Standard_EXPORT gp_Pnt PointOnE2(const int N) const;

  Standard_EXPORT void TrimmedSquareDistances(double& dist11,
                                              double& distP12,
                                              double& distP21,
                                              double& distP22,
                                              gp_Pnt& P11,
                                              gp_Pnt& P12,
                                              gp_Pnt& P21,
                                              gp_Pnt& P22) const;

private:
  Extrema_ExtCC                  myExtCC;
  occ::handle<BRepAdaptor_Curve> myHC;
};
