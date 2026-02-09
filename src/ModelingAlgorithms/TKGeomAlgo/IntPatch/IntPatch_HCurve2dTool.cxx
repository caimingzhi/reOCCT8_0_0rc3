#include <IntPatch_HCurve2dTool.hpp>

int IntPatch_HCurve2dTool::NbSamples(const occ::handle<Adaptor2d_Curve2d>& C,
                                     const double                          U0,
                                     const double                          U1)
{
  double nbs;
  switch (C->GetType())
  {
    case GeomAbs_Line:
      return 2;
    case GeomAbs_BezierCurve:
    {
      nbs = (3 + C->NbPoles());
    }
    break;
    case GeomAbs_BSplineCurve:
    {
      nbs = C->NbKnots();
      nbs *= C->Degree();

      nbs *= U1 - U0;
      nbs /= C->LastParameter() - C->FirstParameter();
      if (nbs < 2.0)
        nbs = 2.0;
    }
    break;
    default:
      return 25;
  }
  if (nbs > 50.0)
    return 50;
  return ((int)nbs);
}
