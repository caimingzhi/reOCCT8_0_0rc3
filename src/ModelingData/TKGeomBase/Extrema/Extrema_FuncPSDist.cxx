#include <Extrema_FuncPSDist.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <math_Vector.hpp>

//=================================================================================================

Extrema_FuncPSDist::Extrema_FuncPSDist(const Adaptor3d_Surface& theS, const gp_Pnt& theP)
    : mySurf(theS),
      myP(theP)
{
}

//=================================================================================================

int Extrema_FuncPSDist::NbVariables() const
{
  return 2;
}

//=================================================================================================

bool Extrema_FuncPSDist::Value(const math_Vector& X, double& F)
{
  if (!IsInside(X))
    return false;

  F = mySurf.Value(X(1), X(2)).SquareDistance(myP);

  return true;
}

//=================================================================================================

bool Extrema_FuncPSDist::Gradient(const math_Vector& X, math_Vector& G)

{
  if (!IsInside(X))
    return false;

  gp_Pnt aP;
  gp_Vec Du1s, Dv1s;
  mySurf.D1(X(1), X(2), aP, Du1s, Dv1s);

  gp_Vec P1P2(aP, myP);

  G(1) = P1P2.Dot(Du1s);
  G(2) = P1P2.Dot(Dv1s);

  return true;
}

//=================================================================================================

bool Extrema_FuncPSDist::Values(const math_Vector& X, double& F, math_Vector& G)
{
  if (!IsInside(X))
    return false;

  gp_Pnt aP;
  gp_Vec Du1s, Dv1s;
  mySurf.D1(X(1), X(2), aP, Du1s, Dv1s);

  gp_Vec P1P2(aP, myP);

  G(1) = P1P2.Dot(Du1s);
  G(2) = P1P2.Dot(Dv1s);

  F = mySurf.Value(X(1), X(2)).SquareDistance(myP);

  return true;
}

//=================================================================================================

bool Extrema_FuncPSDist::IsInside(const math_Vector& X)
{
  return X(1) >= mySurf.FirstUParameter() && X(1) <= mySurf.LastUParameter()
         && X(2) >= mySurf.FirstVParameter() && X(2) <= mySurf.LastVParameter();
}
