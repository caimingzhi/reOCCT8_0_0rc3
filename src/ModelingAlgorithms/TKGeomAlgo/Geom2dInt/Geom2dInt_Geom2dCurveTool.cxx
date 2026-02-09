#include <Geom2d_BezierCurve.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>
#include <GeomAbs_CurveType.hpp>
#include <Precision.hpp>

int Geom2dInt_Geom2dCurveTool::NbSamples(const Adaptor2d_Curve2d& C,
                                         const double             U0,
                                         const double             U1)
{
  GeomAbs_CurveType typC = C.GetType();
  int               nbs  = C.NbSamples();

  if (typC == GeomAbs_BSplineCurve)
  {
    double t = C.LastParameter() - C.FirstParameter();
    if (t > Precision::PConfusion())
    {
      double t1 = U1 - U0;
      if (t1 < 0.0)
        t1 = -t1;
      nbs = C.NbKnots();
      nbs *= C.Degree();
      double anb = t1 / t * nbs;
      nbs        = (int)anb;

      int aMinPntNb = std::max(C.Degree() + 1, 4);
      if (nbs < aMinPntNb)
        nbs = aMinPntNb;
    }
  }
  else if (typC == GeomAbs_Circle)
  {

    const double minR = 1.;
    double       R    = C.Circle().Radius();
    if (R > minR)
    {
      double angl = 0.283079;
      int    n    = RealToInt(std::abs(U1 - U0) / angl);
      nbs         = std::max(n, nbs);
    }
  }

  if (nbs > 300)
    nbs = 300;
  return nbs;
}

int Geom2dInt_Geom2dCurveTool::NbSamples(const Adaptor2d_Curve2d& C)
{
  int               nbs  = C.NbSamples();
  GeomAbs_CurveType typC = C.GetType();
  if (typC == GeomAbs_Circle)
  {

    const double minR = 1.;
    double       R    = C.Circle().Radius();
    if (R > minR)
    {
      double angl = 0.283079;
      int    n    = RealToInt((C.LastParameter() - C.FirstParameter()) / angl);
      nbs         = std::max(n, nbs);
    }
  }

  return nbs;
}
