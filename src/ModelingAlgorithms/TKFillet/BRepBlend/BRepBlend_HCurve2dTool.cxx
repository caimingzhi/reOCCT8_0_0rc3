#include <BRepBlend_HCurve2dTool.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <GeomAbs_CurveType.hpp>

int BRepBlend_HCurve2dTool::NbSamples(const occ::handle<Adaptor2d_Curve2d>& C,
                                      const double                          U0,
                                      const double                          U1)
{
  GeomAbs_CurveType typC     = C->GetType();
  static double     nbsOther = 10.0;
  double            nbs      = nbsOther;

  if (typC == GeomAbs_Line)
    nbs = 2;
  else if (typC == GeomAbs_BezierCurve)
    nbs = 3 + C->Bezier()->NbPoles();
  else if (typC == GeomAbs_BSplineCurve)
  {
    occ::handle<Geom2d_BSplineCurve> BSC = C->BSpline();
    nbs                                  = BSC->NbKnots();
    nbs *= BSC->Degree();
    nbs *= BSC->LastParameter() - BSC->FirstParameter();
    nbs /= U1 - U0;
    if (nbs < 2.0)
      nbs = 2;
  }
  if (nbs > 50)
    nbs = 50;
  return ((int)nbs);
}
