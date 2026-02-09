#include <Adaptor3d_Curve.hpp>
#include <Extrema_CurveTool.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <gp_Pnt.hpp>
#include <GCPnts_TangentialDeflection.hpp>

bool Extrema_CurveTool::IsPeriodic(const Adaptor3d_Curve& C)
{
  GeomAbs_CurveType aType = GetType(C);
  if (aType == GeomAbs_Circle || aType == GeomAbs_Ellipse)
    return true;
  else
    return C.IsPeriodic();
}

occ::handle<NCollection_HArray1<double>> Extrema_CurveTool::DeflCurvIntervals(
  const Adaptor3d_Curve& C)
{
  const double                             epsd    = 1.e-3;
  const double                             maxdefl = 1.e3;
  const double                             mindefl = 1.e-3;
  occ::handle<NCollection_HArray1<double>> Intervals;
  int                                      nbpnts = 23, i;
  double                                   L      = 0.;
  double                                   tf = C.FirstParameter(), tl = C.LastParameter();
  gp_Pnt                                   aP = C.Value(tf);
  for (i = 2; i <= nbpnts; ++i)
  {
    double t   = (tf * (nbpnts - i) + (i - 1) * tl) / (nbpnts - 1);
    gp_Pnt aP1 = C.Value(t);
    L += aP.Distance(aP1);
  }

  double dLdt = L / (tl - tf);
  if (L <= Precision::Confusion() || dLdt < epsd || (tl - tf) > 10000.)
  {
    nbpnts    = 2;
    Intervals = new NCollection_HArray1<double>(1, nbpnts);
    Intervals->SetValue(1, tf);
    Intervals->SetValue(nbpnts, tl);
    return Intervals;
  }

  double aDefl = std::max(0.01 * L / (2. * M_PI), mindefl);
  if (aDefl > maxdefl)
  {
    nbpnts    = 2;
    Intervals = new NCollection_HArray1<double>(1, nbpnts);
    Intervals->SetValue(1, tf);
    Intervals->SetValue(nbpnts, tl);
    return Intervals;
  }

  double aMinLen = std::max(.00001 * L, Precision::Confusion());
  double aTol    = std::max(0.00001 * (tl - tf), Precision::PConfusion());

  GCPnts_TangentialDeflection aPntGen(C, M_PI / 6, aDefl, 2, aTol, aMinLen);
  nbpnts    = aPntGen.NbPoints();
  Intervals = new NCollection_HArray1<double>(1, nbpnts);
  for (i = 1; i <= nbpnts; ++i)
  {
    Intervals->SetValue(i, aPntGen.Parameter(i));
  }
  return Intervals;
}
