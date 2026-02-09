#include <Extrema_GlobOptFuncCC.hpp>

#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <math_Vector.hpp>

static int _NbVariables()
{
  return 2;
}

static bool _Value(const Adaptor3d_Curve& C1,
                   const Adaptor3d_Curve& C2,
                   const math_Vector&     X,
                   double&                F)
{
  double u = X(1);
  double v = X(2);

  if (u < C1.FirstParameter() || u > C1.LastParameter() || v < C2.FirstParameter()
      || v > C2.LastParameter())
  {
    return false;
  }

  F = C2.Value(v).Distance(C1.Value(u));
  return true;
}

static bool _Value(const Adaptor2d_Curve2d& C1,
                   const Adaptor2d_Curve2d& C2,
                   const math_Vector&       X,
                   double&                  F)
{
  double u = X(1);
  double v = X(2);

  if (u < C1.FirstParameter() || u > C1.LastParameter() || v < C2.FirstParameter()
      || v > C2.LastParameter())
  {
    return false;
  }

  F = C2.Value(v).Distance(C1.Value(u));
  return true;
}

static bool _Gradient(const Adaptor3d_Curve& C1,
                      const Adaptor3d_Curve& C2,
                      const math_Vector&     X,
                      math_Vector&           G)
{
  gp_Pnt C1D0, C2D0;
  gp_Vec C1D1, C2D1;

  if (X(1) < C1.FirstParameter() || X(1) > C1.LastParameter() || X(2) < C2.FirstParameter()
      || X(2) > C2.LastParameter())
  {
    return false;
  }

  C1.D1(X(1), C1D0, C1D1);
  C2.D1(X(2), C2D0, C2D1);

  G(1) = -(C2D0.X() - C1D0.X()) * C1D1.X() - (C2D0.Y() - C1D0.Y()) * C1D1.Y()
         - (C2D0.Z() - C1D0.Z()) * C1D1.Z();
  G(2) = (C2D0.X() - C1D0.X()) * C2D1.X() + (C2D0.Y() - C1D0.Y()) * C2D1.Y()
         + (C2D0.Z() - C1D0.Z()) * C2D1.Z();
  G *= 2.;
  return true;
}

static bool _Gradient(const Adaptor2d_Curve2d& C1,
                      const Adaptor2d_Curve2d& C2,
                      const math_Vector&       X,
                      math_Vector&             G)
{
  gp_Pnt2d C1D0, C2D0;
  gp_Vec2d C1D1, C2D1;

  if (X(1) < C1.FirstParameter() || X(1) > C1.LastParameter() || X(2) < C2.FirstParameter()
      || X(2) > C2.LastParameter())
  {
    return false;
  }

  C1.D1(X(1), C1D0, C1D1);
  C2.D1(X(2), C2D0, C2D1);

  G(1) = -(C2D0.X() - C1D0.X()) * C1D1.X() - (C2D0.Y() - C1D0.Y()) * C1D1.Y();

  G(2) = (C2D0.X() - C1D0.X()) * C2D1.X() + (C2D0.Y() - C1D0.Y()) * C2D1.Y();
  G *= 2.;

  return true;
}

static bool _Hessian(const Adaptor3d_Curve& C1,
                     const Adaptor3d_Curve& C2,
                     const math_Vector&     X,
                     math_Matrix&           H)
{
  gp_Pnt C1D0, C2D0;
  gp_Vec C1D1, C2D1;
  gp_Vec C1D2, C2D2;

  if (X(1) < C1.FirstParameter() || X(1) > C1.LastParameter() || X(2) < C2.FirstParameter()
      || X(2) > C2.LastParameter())
  {
    return false;
  }

  C1.D2(X(1), C1D0, C1D1, C1D2);
  C2.D2(X(2), C2D0, C2D1, C2D2);

  H(1, 1) = C1D1.X() * C1D1.X() + C1D1.Y() * C1D1.Y() + C1D1.Z() * C1D1.Z()
            - (C2D0.X() - C1D0.X()) * C1D2.X() - (C2D0.Y() - C1D0.Y()) * C1D2.Y()
            - (C2D0.Z() - C1D0.Z()) * C1D2.Z();

  H(1, 2) = -C2D1.X() * C1D1.X() - C2D1.Y() * C1D1.Y() - C2D1.Z() * C1D1.Z();

  H(2, 1) = H(1, 2);

  H(2, 2) = C2D1.X() * C2D1.X() + C2D1.Y() * C2D1.Y() + C2D1.Z() * C2D1.Z()
            + (C2D0.X() - C1D0.X()) * C2D2.X() + (C2D0.Y() - C1D0.Y()) * C2D2.Y()
            + (C2D0.Z() - C1D0.Z()) * C2D2.Z();
  H *= 2.;
  return true;
}

static bool _Hessian(const Adaptor2d_Curve2d& C1,
                     const Adaptor2d_Curve2d& C2,
                     const math_Vector&       X,
                     math_Matrix&             H)
{
  gp_Pnt2d C1D0, C2D0;
  gp_Vec2d C1D1, C2D1;
  gp_Vec2d C1D2, C2D2;

  if (X(1) < C1.FirstParameter() || X(1) > C1.LastParameter() || X(2) < C2.FirstParameter()
      || X(2) > C2.LastParameter())
  {
    return false;
  }

  C1.D2(X(1), C1D0, C1D1, C1D2);
  C2.D2(X(2), C2D0, C2D1, C2D2);

  H(1, 1) = C1D1.X() * C1D1.X() + C1D1.Y() * C1D1.Y() - (C2D0.X() - C1D0.X()) * C1D2.X()
            - (C2D0.Y() - C1D0.Y()) * C1D2.Y();

  H(1, 2) = -C2D1.X() * C1D1.X() - C2D1.Y() * C1D1.Y();

  H(2, 1) = H(1, 2);

  H(2, 2) = C2D1.X() * C2D1.X() + C2D1.Y() * C2D1.Y() + (C2D0.X() - C1D0.X()) * C2D2.X()
            + (C2D0.Y() - C1D0.Y()) * C2D2.Y();
  H *= 2.;
  return true;
}

Extrema_GlobOptFuncCCC0::Extrema_GlobOptFuncCCC0(const Adaptor3d_Curve& C1,
                                                 const Adaptor3d_Curve& C2)
    : myC1_3d(&C1),
      myC2_3d(&C2),
      myC1_2d(nullptr),
      myC2_2d(nullptr)
{
  myType = 1;
}

Extrema_GlobOptFuncCCC0::Extrema_GlobOptFuncCCC0(const Adaptor2d_Curve2d& C1,
                                                 const Adaptor2d_Curve2d& C2)
    : myC1_3d(nullptr),
      myC2_3d(nullptr),
      myC1_2d(&C1),
      myC2_2d(&C2)
{
  myType = 2;
}

int Extrema_GlobOptFuncCCC0::NbVariables() const
{
  return _NbVariables();
}

bool Extrema_GlobOptFuncCCC0::Value(const math_Vector& X, double& F)
{
  if (myType == 1)
    return _Value(*myC1_3d, *myC2_3d, X, F);
  else
    return _Value(*myC1_2d, *myC2_2d, X, F);
}

Extrema_GlobOptFuncCCC1::Extrema_GlobOptFuncCCC1(const Adaptor3d_Curve& C1,
                                                 const Adaptor3d_Curve& C2)
    : myC1_3d(&C1),
      myC2_3d(&C2),
      myC1_2d(nullptr),
      myC2_2d(nullptr)
{
  myType = 1;
}

Extrema_GlobOptFuncCCC1::Extrema_GlobOptFuncCCC1(const Adaptor2d_Curve2d& C1,
                                                 const Adaptor2d_Curve2d& C2)
    : myC1_3d(nullptr),
      myC2_3d(nullptr),
      myC1_2d(&C1),
      myC2_2d(&C2)
{
  myType = 2;
}

int Extrema_GlobOptFuncCCC1::NbVariables() const
{
  return _NbVariables();
}

bool Extrema_GlobOptFuncCCC1::Value(const math_Vector& X, double& F)
{
  if (myType == 1)
    return _Value(*myC1_3d, *myC2_3d, X, F);
  else
    return _Value(*myC1_2d, *myC2_2d, X, F);
}

bool Extrema_GlobOptFuncCCC1::Gradient(const math_Vector& X, math_Vector& G)
{
  if (myType == 1)
    return _Gradient(*myC1_3d, *myC2_3d, X, G);
  else
    return _Gradient(*myC1_2d, *myC2_2d, X, G);
}

bool Extrema_GlobOptFuncCCC1::Values(const math_Vector& X, double& F, math_Vector& G)
{
  return (Value(X, F) && Gradient(X, G));
}

Extrema_GlobOptFuncCCC2::Extrema_GlobOptFuncCCC2(const Adaptor3d_Curve& C1,
                                                 const Adaptor3d_Curve& C2)
    : myC1_3d(&C1),
      myC2_3d(&C2),
      myC1_2d(nullptr),
      myC2_2d(nullptr)
{
  myType = 1;
}

Extrema_GlobOptFuncCCC2::Extrema_GlobOptFuncCCC2(const Adaptor2d_Curve2d& C1,
                                                 const Adaptor2d_Curve2d& C2)
    : myC1_3d(nullptr),
      myC2_3d(nullptr),
      myC1_2d(&C1),
      myC2_2d(&C2)
{
  myType = 2;
}

int Extrema_GlobOptFuncCCC2::NbVariables() const
{
  return _NbVariables();
}

bool Extrema_GlobOptFuncCCC2::Value(const math_Vector& X, double& F)
{
  if (myType == 1)
    return _Value(*myC1_3d, *myC2_3d, X, F);
  else
    return _Value(*myC1_2d, *myC2_2d, X, F);
}

bool Extrema_GlobOptFuncCCC2::Gradient(const math_Vector& X, math_Vector& G)
{
  if (myType == 1)
    return _Gradient(*myC1_3d, *myC2_3d, X, G);
  else
    return _Gradient(*myC1_2d, *myC2_2d, X, G);
}

bool Extrema_GlobOptFuncCCC2::Values(const math_Vector& X, double& F, math_Vector& G)
{
  return (Value(X, F) && Gradient(X, G));
}

bool Extrema_GlobOptFuncCCC2::Values(const math_Vector& X,
                                     double&            F,
                                     math_Vector&       G,
                                     math_Matrix&       H)
{
  bool isHessianComputed = false;
  if (myType == 1)
    isHessianComputed = _Hessian(*myC1_3d, *myC2_3d, X, H);
  else
    isHessianComputed = _Hessian(*myC1_2d, *myC2_2d, X, H);

  return (Value(X, F) && Gradient(X, G) && isHessianComputed);
}
