

#include <Convert_ParabolaToBSplineCurve.hpp>
#include <gp.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

static int TheDegree  = 2;
static int MaxNbKnots = 2;
static int MaxNbPoles = 3;

Convert_ParabolaToBSplineCurve::Convert_ParabolaToBSplineCurve(const gp_Parab2d& Prb,
                                                               const double      U1,
                                                               const double      U2)
    : Convert_ConicToBSplineCurve(MaxNbPoles, MaxNbKnots, TheDegree)
{
  Standard_DomainError_Raise_if(std::abs(U2 - U1) < Epsilon(0.), "Convert_ParabolaToBSplineCurve");

  double UF = std::min(U1, U2);
  double UL = std::max(U1, U2);

  double p = Prb.Parameter();

  nbPoles                  = 3;
  nbKnots                  = 2;
  isperiodic               = false;
  knots->ChangeArray1()(1) = UF;
  mults->ChangeArray1()(1) = 3;
  knots->ChangeArray1()(2) = UL;
  mults->ChangeArray1()(2) = 3;

  weights->ChangeArray1()(1) = 1.;
  weights->ChangeArray1()(2) = 1.;
  weights->ChangeArray1()(3) = 1.;

  gp_Dir2d Ox = Prb.Axis().XDirection();
  gp_Dir2d Oy = Prb.Axis().YDirection();
  double   S  = (Ox.X() * Oy.Y() - Ox.Y() * Oy.X() > 0.) ? 1 : -1;

  poles->ChangeArray1()(1) = gp_Pnt2d((UF * UF) / (2. * p), S * UF);
  poles->ChangeArray1()(2) = gp_Pnt2d((UF * UL) / (2. * p), S * (UF + UL) / 2.);
  poles->ChangeArray1()(3) = gp_Pnt2d((UL * UL) / (2. * p), S * UL);

  gp_Trsf2d Trsf;
  Trsf.SetTransformation(Prb.Axis().XAxis(), gp::OX2d());
  poles->ChangeArray1()(1).Transform(Trsf);
  poles->ChangeArray1()(2).Transform(Trsf);
  poles->ChangeArray1()(3).Transform(Trsf);
}
