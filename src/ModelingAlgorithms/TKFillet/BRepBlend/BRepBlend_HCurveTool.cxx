#include <BRepBlend_HCurveTool.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <GeomAbs_CurveType.hpp>

//============================================================
int BRepBlend_HCurveTool::NbSamples(const occ::handle<Adaptor3d_Curve>& C,
                                    const double                        U0,
                                    const double                        U1)
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
    occ::handle<Geom_BSplineCurve> BSC = C->BSpline();
    nbs                                = BSC->NbKnots();
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
