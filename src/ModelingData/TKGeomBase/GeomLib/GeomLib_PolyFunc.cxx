#include <GeomLib_PolyFunc.hpp>
#include <math_Vector.hpp>
#include <PLib.hpp>

GeomLib_PolyFunc::GeomLib_PolyFunc(const math_Vector& Coeffs)
    : myCoeffs(1, Coeffs.Length() - 1)
{ // On construit le polynome derive
  for (int ii = 1; ii <= myCoeffs.Length(); ii++)
    myCoeffs(ii) = ii * Coeffs(ii + 1);
}

bool GeomLib_PolyFunc::Value(const double X, double& F)
{
  double* coeff = &myCoeffs(1);
  double* ff    = &F;
  PLib::EvalPolynomial(X, 0, myCoeffs.Length() - 1, 1, coeff[0], ff[0]);
  return true;
}

bool GeomLib_PolyFunc::Derivative(const double X, double& D)
{
  double*     coeff = &myCoeffs(1);
  math_Vector Aux(1, 2);
  double*     ff = &Aux(1);
  PLib::EvalPolynomial(X, 1, myCoeffs.Length() - 1, 1, coeff[0], ff[0]);
  D = Aux(2);
  return true;
}

bool GeomLib_PolyFunc::Values(const double X, double& F, double& D)
{
  double*     coeff = &myCoeffs(1);
  math_Vector Aux(1, 2);
  double*     ff = &Aux(1);
  PLib::EvalPolynomial(X, 1, myCoeffs.Length() - 1, 1, coeff[0], ff[0]);
  F = Aux(1);
  D = Aux(2);
  return true;
}
