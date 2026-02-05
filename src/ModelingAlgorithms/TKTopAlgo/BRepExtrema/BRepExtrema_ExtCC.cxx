#include <BRepExtrema_ExtCC.hpp>

#include <BRep_Tool.hpp>
#include <Extrema_POnCurv.hpp>
#include <BRepAdaptor_Curve.hpp>

//=================================================================================================

BRepExtrema_ExtCC::BRepExtrema_ExtCC(const TopoDS_Edge& E1, const TopoDS_Edge& E2)
{
  Initialize(E2);
  Perform(E1);
}

//=================================================================================================

void BRepExtrema_ExtCC::Initialize(const TopoDS_Edge& E2)
{
  if (!BRep_Tool::IsGeometric(E2))
    return; // protect against non-geometric type (e.g. polygon)
  double            V1, V2;
  BRepAdaptor_Curve Curv(E2);
  myHC       = new BRepAdaptor_Curve(Curv);
  double Tol = std::min(BRep_Tool::Tolerance(E2), Precision::Confusion());
  Tol        = std::max(Curv.Resolution(Tol), Precision::PConfusion());
  BRep_Tool::Range(E2, V1, V2);
  myExtCC.SetCurve(2, *myHC, V1, V2);
  myExtCC.SetTolerance(2, Tol);
}

//=================================================================================================

void BRepExtrema_ExtCC::Perform(const TopoDS_Edge& E1)
{
  if (!BRep_Tool::IsGeometric(E1))
    return; // protect against non-geometric type (e.g. polygon)
  double                         U1, U2;
  BRepAdaptor_Curve              Curv(E1);
  occ::handle<BRepAdaptor_Curve> HC  = new BRepAdaptor_Curve(Curv);
  double                         Tol = std::min(BRep_Tool::Tolerance(E1), Precision::Confusion());
  Tol                                = std::max(Curv.Resolution(Tol), Precision::PConfusion());
  BRep_Tool::Range(E1, U1, U2);
  myExtCC.SetCurve(1, *HC, U1, U2);
  myExtCC.SetTolerance(1, Tol);
  // If we enable SetSingleSolutionFlag Extrema will run much quicker on almost parallel curves
  // (e.g. bug 27665), however some solutions will be lost, e.g. see bug 28183.
  // myExtCC.SetSingleSolutionFlag(true);
  myExtCC.Perform();
}

//=================================================================================================

double BRepExtrema_ExtCC::ParameterOnE1(const int N) const
{
  Extrema_POnCurv POnE1, POnE2;
  myExtCC.Points(N, POnE1, POnE2);
  return POnE1.Parameter();
}

//=================================================================================================

gp_Pnt BRepExtrema_ExtCC::PointOnE1(const int N) const
{
  Extrema_POnCurv POnE1, POnE2;
  myExtCC.Points(N, POnE1, POnE2);
  return POnE1.Value();
}

//=================================================================================================

double BRepExtrema_ExtCC::ParameterOnE2(const int N) const
{
  Extrema_POnCurv POnE1, POnE2;
  myExtCC.Points(N, POnE1, POnE2);
  return POnE2.Parameter();
}

//=================================================================================================

gp_Pnt BRepExtrema_ExtCC::PointOnE2(const int N) const
{
  Extrema_POnCurv POnE1, POnE2;
  myExtCC.Points(N, POnE1, POnE2);
  return POnE2.Value();
}

//=================================================================================================

void BRepExtrema_ExtCC::TrimmedSquareDistances(double& dist11,
                                               double& dist12,
                                               double& dist21,
                                               double& dist22,
                                               gp_Pnt& pnt11,
                                               gp_Pnt& pnt12,
                                               gp_Pnt& pnt21,
                                               gp_Pnt& pnt22) const
{
  myExtCC.TrimmedSquareDistances(dist11, dist12, dist21, dist22, pnt11, pnt12, pnt21, pnt22);
}
