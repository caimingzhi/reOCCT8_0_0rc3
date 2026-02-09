

#include <Convert_HyperbolaToBSplineCurve.hpp>
#include <gp.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

static int TheDegree  = 2;
static int MaxNbKnots = 2;
static int MaxNbPoles = 3;

Convert_HyperbolaToBSplineCurve::Convert_HyperbolaToBSplineCurve(const gp_Hypr2d& H,
                                                                 const double     U1,
                                                                 const double     U2)

    : Convert_ConicToBSplineCurve(MaxNbPoles, MaxNbKnots, TheDegree)
{
  Standard_DomainError_Raise_if(std::abs(U2 - U1) < Epsilon(0.), "Convert_ParabolaToBSplineCurve");

  double UF = std::min(U1, U2);
  double UL = std::max(U1, U2);

  nbPoles                  = 3;
  nbKnots                  = 2;
  isperiodic               = false;
  knots->ChangeArray1()(1) = UF;
  mults->ChangeArray1()(1) = 3;
  knots->ChangeArray1()(2) = UL;
  mults->ChangeArray1()(2) = 3;

  double   R  = H.MajorRadius();
  double   r  = H.MinorRadius();
  gp_Dir2d Ox = H.Axis().XDirection();
  gp_Dir2d Oy = H.Axis().YDirection();
  double   S  = (Ox.X() * Oy.Y() - Ox.Y() * Oy.X() > 0.) ? 1 : -1;

  weights->ChangeArray1()(1) = 1.;
  weights->ChangeArray1()(2) = std::cosh((UL - UF) / 2);
  weights->ChangeArray1()(3) = 1.;

  double delta             = std::sinh(UL - UF);
  double x                 = R * (std::sinh(UL) - std::sinh(UF)) / delta;
  double y                 = S * r * (std::cosh(UL) - std::cosh(UF)) / delta;
  poles->ChangeArray1()(1) = gp_Pnt2d(R * std::cosh(UF), S * r * std::sinh(UF));
  poles->ChangeArray1()(2) = gp_Pnt2d(x, y);
  poles->ChangeArray1()(3) = gp_Pnt2d(R * std::cosh(UL), S * r * std::sinh(UL));

  gp_Trsf2d Trsf;
  Trsf.SetTransformation(H.Axis().XAxis(), gp::OX2d());
  poles->ChangeArray1()(1).Transform(Trsf);
  poles->ChangeArray1()(2).Transform(Trsf);
  poles->ChangeArray1()(3).Transform(Trsf);
}
