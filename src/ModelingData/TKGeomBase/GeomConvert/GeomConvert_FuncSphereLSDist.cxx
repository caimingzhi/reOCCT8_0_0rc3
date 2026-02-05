#include <GeomConvert_FuncSphereLSDist.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <math_Vector.hpp>

//=================================================================================================

GeomConvert_FuncSphereLSDist::GeomConvert_FuncSphereLSDist(
  const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints)
    : myPoints(thePoints)
{
}

//=================================================================================================

int GeomConvert_FuncSphereLSDist::NbVariables() const
{
  return 4;
}

//=================================================================================================

bool GeomConvert_FuncSphereLSDist::Value(const math_Vector& X, double& F)
{
  gp_XYZ aLoc(X(1), X(2), X(3));
  double anR2 = X(4) * X(4);

  F = 0.;
  int i;
  for (i = myPoints->Lower(); i <= myPoints->Upper(); ++i)
  {
    double d = (myPoints->Value(i) - aLoc).SquareModulus() - anR2;
    F += d * d;
  }

  return true;
}

//=================================================================================================

bool GeomConvert_FuncSphereLSDist::Gradient(const math_Vector& X, math_Vector& G)

{
  gp_XYZ aLoc(X(1), X(2), X(3));
  double anR = X(4), anR2 = anR * anR;

  G.Init(0.);
  int i;
  for (i = myPoints->Lower(); i <= myPoints->Upper(); ++i)
  {
    gp_XYZ dLoc = myPoints->Value(i) - aLoc;
    double d    = dLoc.SquareModulus() - anR2;
    G(1) += d * dLoc.X();
    G(2) += d * dLoc.Y();
    G(3) += d * dLoc.Z();
    G(4) += d;
  }
  G *= -4;
  G(4) *= anR;

  return true;
}

//=================================================================================================

bool GeomConvert_FuncSphereLSDist::Values(const math_Vector& X, double& F, math_Vector& G)
{
  gp_XYZ aLoc(X(1), X(2), X(3));
  double anR = X(4), anR2 = anR * anR;

  G.Init(0.);
  F = 0.;
  int i;
  for (i = myPoints->Lower(); i <= myPoints->Upper(); ++i)
  {
    gp_XYZ dLoc = myPoints->Value(i) - aLoc;
    double d    = dLoc.SquareModulus() - anR2;
    G(1) += d * dLoc.X();
    G(2) += d * dLoc.Y();
    G(3) += d * dLoc.Z();
    G(4) += d;
    F += d * d;
  }
  G *= -4;
  G(4) *= anR;

  return true;
}
