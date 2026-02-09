

#include <GeomConvert_FuncCylinderLSDist.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <math_Vector.hpp>

GeomConvert_FuncCylinderLSDist::GeomConvert_FuncCylinderLSDist(
  const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints,
  const gp_Dir&                                   theDir)
    : myPoints(thePoints),
      myDir(theDir)
{
}

int GeomConvert_FuncCylinderLSDist::NbVariables() const
{
  return 4;
}

bool GeomConvert_FuncCylinderLSDist::Value(const math_Vector& X, double& F)
{
  gp_XYZ aLoc(X(1), X(2), X(3));
  double anR2 = X(4) * X(4);

  F = 0.;
  int i;
  for (i = myPoints->Lower(); i <= myPoints->Upper(); ++i)
  {
    gp_Vec aV(myPoints->Value(i) - aLoc);
    double aD2 = aV.CrossSquareMagnitude(myDir);
    double d   = aD2 - anR2;
    F += d * d;
  }

  return true;
}

bool GeomConvert_FuncCylinderLSDist::Gradient(const math_Vector& X, math_Vector& G)

{
  gp_XYZ aLoc(X(1), X(2), X(3));
  double anR = X(4), anR2 = anR * anR;
  double x = myDir.X(), y = myDir.Y(), z = myDir.Z();
  G.Init(0.);

  int i;
  for (i = myPoints->Lower(); i <= myPoints->Upper(); ++i)
  {
    gp_Vec aV(myPoints->Value(i) - aLoc);
    double aD2 = aV.CrossSquareMagnitude(myDir);
    double d   = aD2 - anR2;
    double Dx0 = 2. * (aV.Z() * x - aV.X() * z) * z - 2. * (aV.X() * y - aV.Y() * x) * y;
    double Dy0 = -2. * (aV.Y() * z - aV.Z() * y) * z + 2. * (aV.X() * y - aV.Y() * x) * x;
    double Dz0 = 2. * (aV.Y() * z - aV.Z() * y) * y - 2. * (aV.Z() * x - aV.X() * z) * x;

    G(1) += d * Dx0;
    G(2) += d * Dy0;
    G(3) += d * Dz0;

    G(4) += d;
  }

  G *= 2;
  G(6) *= -2. * anR;

  return true;
}

bool GeomConvert_FuncCylinderLSDist::Values(const math_Vector& X, double& F, math_Vector& G)
{
  gp_XYZ aLoc(X(1), X(2), X(3));
  double anR = X(4), anR2 = anR * anR;
  double x = myDir.X(), y = myDir.Y(), z = myDir.Z();

  F = 0.;
  G.Init(0.);
  int i;
  for (i = myPoints->Lower(); i <= myPoints->Upper(); ++i)
  {
    gp_Vec aV(myPoints->Value(i) - aLoc);
    double aD2 = aV.CrossSquareMagnitude(myDir);
    double d   = aD2 - anR2;
    double Dx0 = 2. * (aV.Z() * x - aV.X() * z) * z - 2. * (aV.X() * y - aV.Y() * x) * y;
    double Dy0 = -2. * (aV.Y() * z - aV.Z() * y) * z + 2. * (aV.X() * y - aV.Y() * x) * x;
    double Dz0 = 2. * (aV.Y() * z - aV.Z() * y) * y - 2. * (aV.Z() * x - aV.X() * z) * x;

    G(1) += d * Dx0;
    G(2) += d * Dy0;
    G(3) += d * Dz0;

    G(4) += d;

    F += d * d;
  }

  G *= 2;
  G(4) *= -2. * anR;

  return true;
}
