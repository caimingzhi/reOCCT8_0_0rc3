#include <HLRBRep_CurveTool.hpp>

int HLRBRep_CurveTool::NbSamples(const HLRBRep_CurvePtr C)
{
  GeomAbs_CurveType typC     = ((HLRBRep_Curve*)C)->GetType();
  static double     nbsOther = 10.0;
  double            nbs      = nbsOther;

  if (typC == GeomAbs_Line)
    nbs = 2;
  else if (typC == GeomAbs_BezierCurve)
    nbs = 3 + ((HLRBRep_Curve*)C)->NbPoles();
  else if (typC == GeomAbs_BSplineCurve)
  {
    nbs = ((HLRBRep_Curve*)C)->NbKnots();
    nbs *= ((HLRBRep_Curve*)C)->Degree();
    if (nbs < 2.0)
      nbs = 2;
  }
  if (nbs > 50)
    nbs = 50;
  return ((int)nbs);
}

int HLRBRep_CurveTool::NbSamples(const HLRBRep_CurvePtr C, const double u1, const double u2)
{
  GeomAbs_CurveType typC     = ((HLRBRep_Curve*)C)->GetType();
  static double     nbsOther = 10.0;
  double            nbs      = nbsOther;

  if (typC == GeomAbs_Line)
    nbs = 2;
  else if (typC == GeomAbs_BezierCurve)
    nbs = 3 + ((HLRBRep_Curve*)C)->NbPoles();
  else if (typC == GeomAbs_BSplineCurve)
  {
    occ::handle<Geom_Curve> aCurve = ((HLRBRep_Curve*)C)->Curve().Curve().Curve();
    GeomAdaptor_Curve       GAcurve(aCurve, u1, u2);
    nbs = GAcurve.NbIntervals(GeomAbs_CN) + 1;
    nbs *= ((HLRBRep_Curve*)C)->Degree();
    if (nbs < 2.0)
      nbs = 2;
  }
  if (nbs > 50)
    nbs = 50;
  return ((int)nbs);
}
