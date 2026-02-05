#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Parab2d.hpp>
#include <IntCurve_PConic.hpp>

IntCurve_PConic::IntCurve_PConic(const IntCurve_PConic& PC)

  = default;

IntCurve_PConic::IntCurve_PConic(const gp_Elips2d& E)
    : axe(E.Axis()),
      prm1(E.MajorRadius()),
      prm2(E.MinorRadius()),
      TheEpsX(0.00000001),
      TheAccuracy(20),
      type(GeomAbs_Ellipse)
{
}

IntCurve_PConic::IntCurve_PConic(const gp_Hypr2d& H)
    : axe(H.Axis()),
      prm1(H.MajorRadius()),
      prm2(H.MinorRadius()),
      TheEpsX(0.00000001),
      TheAccuracy(50),
      type(GeomAbs_Hyperbola)
{
}

IntCurve_PConic::IntCurve_PConic(const gp_Circ2d& C)
    : axe(C.Axis()),
      prm1(C.Radius()),
      prm2(0.0),
      TheEpsX(0.00000001),
      TheAccuracy(20),
      type(GeomAbs_Circle)
{
}

IntCurve_PConic::IntCurve_PConic(const gp_Parab2d& P)
    : axe(P.Axis()),
      prm1(P.Focal()),
      prm2(0.0),
      TheEpsX(0.00000001),
      TheAccuracy(20),
      type(GeomAbs_Parabola)
{
}

IntCurve_PConic::IntCurve_PConic(const gp_Lin2d& L)
    : axe(gp_Ax22d(L.Position())),
      prm1(0.0),
      prm2(0.0),
      TheEpsX(0.00000001),
      TheAccuracy(20),
      type(GeomAbs_Line)
{
}

void IntCurve_PConic::SetEpsX(const double epsx)
{
  TheEpsX = epsx;
}

void IntCurve_PConic::SetAccuracy(const int n)
{
  TheAccuracy = n;
}
