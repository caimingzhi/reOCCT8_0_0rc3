

#include <Law_BSpline.hpp>
#include <Law_S.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Law_S, Law_BSpFunc)

Law_S::Law_S() = default;

void Law_S::Set(const double Pdeb, const double Valdeb, const double Pfin, const double Valfin)
{
  Set(Pdeb, Valdeb, 0., Pfin, Valfin, 0.);
}

void Law_S::Set(const double Pdeb,
                const double Valdeb,
                const double Ddeb,
                const double Pfin,
                const double Valfin,
                const double Dfin)
{
  NCollection_Array1<double> poles(1, 4);
  NCollection_Array1<double> knots(1, 2);
  NCollection_Array1<int>    mults(1, 2);
  poles(1)   = Valdeb;
  poles(4)   = Valfin;
  double coe = (Pfin - Pdeb) / 3.;
  poles(2)   = Valdeb + coe * Ddeb;
  poles(3)   = Valfin - coe * Dfin;
  knots(1)   = Pdeb;
  knots(2)   = Pfin;
  mults(1) = mults(2) = 4;

  SetCurve(new Law_BSpline(poles, knots, mults, 3));
}
