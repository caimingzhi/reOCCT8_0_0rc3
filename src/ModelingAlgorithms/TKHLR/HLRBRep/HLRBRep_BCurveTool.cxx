#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <HLRBRep_BCurveTool.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

//=================================================================================================

int HLRBRep_BCurveTool::NbSamples(const BRepAdaptor_Curve& C, const double U0, const double U1)
{
  GeomAbs_CurveType typC     = C.GetType();
  static double     nbsOther = 10.0;
  double            nbs      = nbsOther;

  if (typC == GeomAbs_Line)
    nbs = 2;
  else if (typC == GeomAbs_BezierCurve)
    nbs = 3 + C.NbPoles();
  else if (typC == GeomAbs_BSplineCurve)
  {
    nbs = C.NbKnots();
    nbs *= C.Degree();
    nbs *= C.LastParameter() - C.FirstParameter();
    nbs /= U1 - U0;
    if (nbs < 2.0)
      nbs = 2;
  }
  if (nbs > 50)
    nbs = 50;
  return ((int)nbs);
}

//=================================================================================================

void HLRBRep_BCurveTool::Poles(const BRepAdaptor_Curve& C, NCollection_Array1<gp_Pnt>& T)
{
  if (C.GetType() == GeomAbs_BezierCurve)
    C.Bezier()->Poles(T);
  else if (C.GetType() == GeomAbs_BSplineCurve)
    C.BSpline()->Poles(T);
}

//=================================================================================================

void HLRBRep_BCurveTool::PolesAndWeights(const BRepAdaptor_Curve&    C,
                                         NCollection_Array1<gp_Pnt>& T,
                                         NCollection_Array1<double>& W)
{
  if (C.GetType() == GeomAbs_BezierCurve)
  {
    const occ::handle<Geom_BezierCurve> HB = C.Bezier();
    HB->Poles(T);
    HB->Weights(W);
  }
  else if (C.GetType() == GeomAbs_BSplineCurve)
  {
    const occ::handle<Geom_BSplineCurve> HB = C.BSpline();
    HB->Poles(T);
    HB->Weights(W);
  }
}

//=================================================================================================

occ::handle<Geom_BezierCurve> HLRBRep_BCurveTool::Bezier(const BRepAdaptor_Curve& C)
{
  return (C.Bezier());
}

//=================================================================================================

occ::handle<Geom_BSplineCurve> HLRBRep_BCurveTool::BSpline(const BRepAdaptor_Curve& C)
{
  return (C.BSpline());
}
