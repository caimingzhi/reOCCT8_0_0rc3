#include <Adaptor3d_InterFunc.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_ConstructionError.hpp>

Adaptor3d_InterFunc::Adaptor3d_InterFunc(const occ::handle<Adaptor2d_Curve2d>& C,
                                         const double                          FixVal,
                                         const int                             Fix)
    : myCurve2d(C),
      myFixVal(FixVal),
      myFix(Fix)
{
  if (Fix != 1 && Fix != 2)
    throw Standard_ConstructionError();
}

bool Adaptor3d_InterFunc::Value(const double X, double& F)
{
  gp_Pnt2d C;
  myCurve2d->D0(X, C);
  if (myFix == 1)
    F = C.X() - myFixVal;
  else
    F = C.Y() - myFixVal;

  return true;
}

bool Adaptor3d_InterFunc::Derivative(const double X, double& D)
{
  double F;
  return Values(X, F, D);
}

bool Adaptor3d_InterFunc::Values(const double X, double& F, double& D)
{
  gp_Pnt2d C;
  gp_Vec2d DC;
  myCurve2d->D1(X, C, DC);
  if (myFix == 1)
  {
    F = C.X() - myFixVal;
    D = DC.X();
  }
  else
  {
    F = C.Y() - myFixVal;
    D = DC.Y();
  }
  return true;
}
