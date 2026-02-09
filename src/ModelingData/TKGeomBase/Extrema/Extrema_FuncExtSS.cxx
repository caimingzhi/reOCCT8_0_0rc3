#include <Adaptor3d_Surface.hpp>
#include <Extrema_FuncExtSS.hpp>
#include <Extrema_POnSurf.hpp>
#include <gp_Vec.hpp>
#include <math_Matrix.hpp>
#include <Standard_TypeMismatch.hpp>

Extrema_FuncExtSS::Extrema_FuncExtSS()
    : myS1(nullptr),
      myS2(nullptr),
      myU1(0.0),
      myV1(0.0),
      myU2(0.0),
      myV2(0.0)
{
  myS1init = false;
  myS2init = false;
}

Extrema_FuncExtSS::Extrema_FuncExtSS(const Adaptor3d_Surface& S1, const Adaptor3d_Surface& S2)
    : myU1(0.0),
      myV1(0.0),
      myU2(0.0),
      myV2(0.0)
{
  myS1     = &S1;
  myS2     = &S2;
  myS1init = true;
  myS2init = true;
}

void Extrema_FuncExtSS::Initialize(const Adaptor3d_Surface& S1, const Adaptor3d_Surface& S2)
{
  myS1     = &S1;
  myS2     = &S2;
  myS1init = true;
  myS2init = true;
  myPoint1.Clear();
  myPoint2.Clear();
  mySqDist.Clear();
}

int Extrema_FuncExtSS::NbVariables() const
{
  return 4;
}

int Extrema_FuncExtSS::NbEquations() const
{
  return 4;
}

bool Extrema_FuncExtSS::Value(const math_Vector& UV, math_Vector& F)
{
  if (!myS1init || !myS2init)
    throw Standard_TypeMismatch();
  myU1 = UV(1);
  myV1 = UV(2);
  myU2 = UV(3);
  myV2 = UV(4);
  gp_Vec Du1s1, Dv1s1;
  gp_Vec Du2s2, Dv2s2;
  myS1->D1(myU1, myV1, myP1, Du1s1, Dv1s1);
  myS2->D1(myU2, myV2, myP2, Du2s2, Dv2s2);

  gp_Vec P1P2(myP2, myP1);

  F(1) = P1P2.Dot(Du1s1);
  F(2) = P1P2.Dot(Dv1s1);
  F(3) = P1P2.Dot(Du2s2);
  F(4) = P1P2.Dot(Dv2s2);

  return true;
}

bool Extrema_FuncExtSS::Derivatives(const math_Vector& UV, math_Matrix& Df)
{
  math_Vector F(1, 4);
  return Values(UV, F, Df);
}

bool Extrema_FuncExtSS::Values(const math_Vector& UV, math_Vector& F, math_Matrix& Df)
{
  if (!myS1init || !myS2init)
    throw Standard_TypeMismatch();
  myU1 = UV(1);
  myV1 = UV(2);
  myU2 = UV(3);
  myV2 = UV(4);
  gp_Vec Du1s1, Dv1s1, Du1u1s1, Dv1v1s1, Du1v1s1;
  gp_Vec Du2s2, Dv2s2, Du2u2s2, Dv2v2s2, Du2v2s2;
  myS1->D2(myU1, myV1, myP1, Du1s1, Dv1s1, Du1u1s1, Dv1v1s1, Du1v1s1);
  myS2->D2(myU2, myV2, myP2, Du2s2, Dv2s2, Du2u2s2, Dv2v2s2, Du2v2s2);

  gp_Vec P1P2(myP2, myP1);

  F(1) = P1P2.Dot(Du1s1);
  F(2) = P1P2.Dot(Dv1s1);
  F(3) = P1P2.Dot(Du2s2);
  F(4) = P1P2.Dot(Dv2s2);

  Df(1, 1) = Du1s1.SquareMagnitude() + P1P2.Dot(Du1u1s1);
  Df(1, 2) = Dv1s1.Dot(Du1s1) + P1P2.Dot(Du1v1s1);
  Df(1, 3) = -Du2s2.Dot(Du1s1);
  Df(1, 4) = -Dv2s2.Dot(Du1s1);

  Df(2, 1) = Df(1, 2);
  Df(2, 2) = Dv1s1.SquareMagnitude() + P1P2.Dot(Dv1v1s1);
  Df(2, 3) = -Du2s2.Dot(Dv1s1);
  Df(2, 4) = -Dv2s2.Dot(Dv1s1);

  Df(3, 1) = -Df(1, 3);
  Df(3, 2) = -Df(2, 3);
  Df(3, 3) = -Du2s2.SquareMagnitude() + P1P2.Dot(Du2u2s2);
  Df(3, 4) = -Dv2s2.Dot(Du2s2) + P1P2.Dot(Du2v2s2);

  Df(4, 1) = -Df(1, 4);
  Df(4, 2) = -Df(2, 4);
  Df(4, 3) = Df(3, 4);
  Df(4, 4) = -Dv2s2.SquareMagnitude() + P1P2.Dot(Dv2v2s2);

  return true;
}

int Extrema_FuncExtSS::GetStateNumber()
{
  if (!myS1init || !myS2init)
    throw Standard_TypeMismatch();

  mySqDist.Append(myP1.SquareDistance(myP2));
  myPoint1.Append(Extrema_POnSurf(myU1, myV1, myP1));
  myPoint2.Append(Extrema_POnSurf(myU2, myV2, myP2));
  return 0;
}

int Extrema_FuncExtSS::NbExt() const
{
  return mySqDist.Length();
}

double Extrema_FuncExtSS::SquareDistance(const int N) const
{
  if (!myS1init || !myS2init)
    throw Standard_TypeMismatch();
  return mySqDist.Value(N);
}

const Extrema_POnSurf& Extrema_FuncExtSS::PointOnS1(const int N) const
{
  if (!myS1init || !myS2init)
    throw Standard_TypeMismatch();
  return myPoint1.Value(N);
}

const Extrema_POnSurf& Extrema_FuncExtSS::PointOnS2(const int N) const
{
  if (!myS1init || !myS2init)
    throw Standard_TypeMismatch();
  return myPoint2.Value(N);
}
