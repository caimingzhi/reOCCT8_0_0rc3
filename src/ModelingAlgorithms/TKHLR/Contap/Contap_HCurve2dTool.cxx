#include <Contap_HCurve2dTool.hpp>
#include <Geom2d_BezierCurve.hpp>

//============================================================
int Contap_HCurve2dTool::NbSamples(const occ::handle<Adaptor2d_Curve2d>& C,
                                   const double                          U0,
                                   const double                          U1)
{
  double nbs = 10.0;
  switch (C->GetType())
  {
    case GeomAbs_Line:
      nbs = 2.;
      break;
    case GeomAbs_BezierCurve:
      nbs = 3. + C->NbPoles();
      break;
    case GeomAbs_BSplineCurve:
      nbs = C->NbKnots();
      nbs *= C->Degree();
      nbs *= C->LastParameter() - C->FirstParameter();
      nbs /= U1 - U0;
      if (nbs < 2.0)
        nbs = 2.;
      break;
    default:
      break;
  }
  if (nbs > 50.)
    nbs = 50.;
  return ((int)nbs);
}
