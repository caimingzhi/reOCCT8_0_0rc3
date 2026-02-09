

#include <CPnts_MyRootFunction.hpp>
#include <math_GaussSingleIntegration.hpp>
#include <Standard_DomainError.hpp>

void CPnts_MyRootFunction::Init(const CPnts_RealFunction& F, void* const D, const int Order)
{
  myFunction.Init(F, D);
  myOrder = Order;
}

void CPnts_MyRootFunction::Init(const double X0, const double L)
{
  myX0  = X0;
  myL   = L;
  myTol = -1;
}

void CPnts_MyRootFunction::Init(const double X0, const double L, const double Tol)
{
  myX0  = X0;
  myL   = L;
  myTol = Tol;
}

bool CPnts_MyRootFunction::Value(const double X, double& F)
{
  math_GaussSingleIntegration Length;

  if (myTol <= 0)
    Length = math_GaussSingleIntegration(myFunction, myX0, X, myOrder);
  else
    Length = math_GaussSingleIntegration(myFunction, myX0, X, myOrder, myTol);

  if (Length.IsDone())
  {
    F = Length.Value() - myL;
    return true;
  }
  else
  {
    return false;
  }
}

bool CPnts_MyRootFunction::Derivative(const double X, double& Df)
{
  return myFunction.Value(X, Df);
}

bool CPnts_MyRootFunction::Values(const double X, double& F, double& Df)
{
  math_GaussSingleIntegration Length;

  if (myTol <= 0)
    Length = math_GaussSingleIntegration(myFunction, myX0, X, myOrder);
  else
    Length = math_GaussSingleIntegration(myFunction, myX0, X, myOrder, myTol);

  if (Length.IsDone())
  {
    F = Length.Value() - myL;
    return myFunction.Value(X, Df);
  }
  else
  {
    return false;
  }
}
