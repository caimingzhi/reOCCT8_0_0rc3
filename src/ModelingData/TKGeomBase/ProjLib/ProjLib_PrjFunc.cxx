#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <math_Matrix.hpp>
#include <ProjLib_PrjFunc.hpp>
#include <Standard_ConstructionError.hpp>

ProjLib_PrjFunc::ProjLib_PrjFunc(const Adaptor3d_Curve*   C,
                                 const double             FixVal,
                                 const Adaptor3d_Surface* S,
                                 const int                Fix)
    : myCurve(C),
      mySurface(S),
      myt(0),
      myU(0),
      myV(0),
      myFix(Fix)
{
  myNorm = std::min(1., std::min(mySurface->UResolution(1.), mySurface->VResolution(1.)));

  switch (myFix)
  {
    case 1:
      myt = FixVal;
      break;
    case 2:
      myU = FixVal;
      break;
    case 3:
      myV = FixVal;
      break;
    default:
      throw Standard_ConstructionError();
  }
}

int ProjLib_PrjFunc::NbVariables() const
{
  return 2;
}

int ProjLib_PrjFunc::NbEquations() const
{
  return 2;
}

bool ProjLib_PrjFunc::Value(const math_Vector& X, math_Vector& F)
{
  math_Matrix D(1, 2, 1, 2);
  return Values(X, F, D);
}

bool ProjLib_PrjFunc::Derivatives(const math_Vector& X, math_Matrix& D)
{
  math_Vector F(1, 2);
  return Values(X, F, D);
}

bool ProjLib_PrjFunc::Values(const math_Vector& X, math_Vector& F, math_Matrix& D)
{
  double u = 0., v = 0., t = 0.;
  switch (myFix)
  {
    case 1:
      t = myt;
      u = X(1);
      v = X(2);
      break;
    case 2:
      t = X(1);
      u = myU;
      v = X(2);
      break;
    case 3:
      t = X(1);
      u = X(2);
      v = myV;
  }

  gp_Pnt S, C;
  gp_Vec DS1_u, DS1_v, DS2_u, DS2_uv, DS2_v, DC1_t;
  myCurve->D1(t, C, DC1_t);
  mySurface->D2(u, v, S, DS1_u, DS1_v, DS2_u, DS2_v, DS2_uv);

  gp_Vec V(C, S);

  F(1) = V * DS1_u * myNorm;
  F(2) = V * DS1_v * myNorm;

  switch (myFix)
  {
    case 1:
      D(1, 1) = (DS1_u.SquareMagnitude() + V * DS2_u) * myNorm;
      D(1, 2) = (DS1_v * DS1_u + V * DS2_uv) * myNorm;
      D(2, 1) = D(1, 2);
      D(2, 2) = (DS1_v.SquareMagnitude() + V * DS2_v) * myNorm;
      break;
    case 2:
      D(1, 1) = (-DC1_t * DS1_u) * myNorm;
      D(1, 2) = (DS1_v * DS1_u + V * DS2_uv) * myNorm;
      D(2, 1) = (-DC1_t * DS1_v) * myNorm;
      D(2, 2) = (DS1_v.SquareMagnitude() + V * DS2_v) * myNorm;
      break;
    case 3:
      D(1, 1) = -DC1_t * DS1_u * myNorm;
      D(1, 2) = (DS1_u.SquareMagnitude() + V * DS2_u) * myNorm;
      D(2, 1) = -DC1_t * DS1_v * myNorm;
      D(2, 2) = (DS1_v * DS1_u + V * DS2_uv) * myNorm;
  }

  myU = u;
  myV = v;
  myt = t;

  return true;
}

gp_Pnt2d ProjLib_PrjFunc::Solution() const
{
  switch (myFix)
  {
    case 1:
      return gp_Pnt2d(myU, myV);
    case 2:
      return gp_Pnt2d(myt, myV);
    case 3:
      return gp_Pnt2d(myt, myU);
  }

  return gp_Pnt2d(0., 0.);
}
