#ifndef No_Exception
  #define No_Exception
#endif

#include <ElSLib.hpp>
#include <gp.hpp>
#include <gp_Ax3.hpp>
#include <gp_Circ.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>

namespace
{
  static constexpr double PIPI = M_PI + M_PI;

  static constexpr double NEGATIVE_RESOLUTION = -Precision::Computational();

  static inline void normalizeAngle(double& theAngle)
  {
    while (theAngle < NEGATIVE_RESOLUTION)
    {
      theAngle += PIPI;
    }

    while (theAngle > PIPI * (1.0 + gp::Resolution()))
    {
      theAngle -= PIPI;
    }
    if (theAngle < 0.)
    {
      theAngle = 0.;
    }
  }
} // namespace

gp_Pnt ElSLib::PlaneValue(const double U, const double V, const gp_Ax3& Pos)
{
  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  return gp_Pnt(U * XDir.X() + V * YDir.X() + PLoc.X(),
                U * XDir.Y() + V * YDir.Y() + PLoc.Y(),
                U * XDir.Z() + V * YDir.Z() + PLoc.Z());
}

gp_Pnt ElSLib::ConeValue(const double  U,
                         const double  V,
                         const gp_Ax3& Pos,
                         const double  Radius,
                         const double  SAngle)
{
  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        R    = Radius + V * sin(SAngle);
  double        A3   = V * cos(SAngle);
  double        A1   = R * cos(U);
  double        A2   = R * sin(U);
  return gp_Pnt(A1 * XDir.X() + A2 * YDir.X() + A3 * ZDir.X() + PLoc.X(),
                A1 * XDir.Y() + A2 * YDir.Y() + A3 * ZDir.Y() + PLoc.Y(),
                A1 * XDir.Z() + A2 * YDir.Z() + A3 * ZDir.Z() + PLoc.Z());
}

gp_Pnt ElSLib::CylinderValue(const double U, const double V, const gp_Ax3& Pos, const double Radius)
{

  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        A1   = Radius * cos(U);
  double        A2   = Radius * sin(U);
  return gp_Pnt(A1 * XDir.X() + A2 * YDir.X() + V * ZDir.X() + PLoc.X(),
                A1 * XDir.Y() + A2 * YDir.Y() + V * ZDir.Y() + PLoc.Y(),
                A1 * XDir.Z() + A2 * YDir.Z() + V * ZDir.Z() + PLoc.Z());
}

gp_Pnt ElSLib::SphereValue(const double U, const double V, const gp_Ax3& Pos, const double Radius)
{

  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        R    = Radius * cos(V);
  double        A3   = Radius * sin(V);
  double        A1   = R * cos(U);
  double        A2   = R * sin(U);
  return gp_Pnt(A1 * XDir.X() + A2 * YDir.X() + A3 * ZDir.X() + PLoc.X(),
                A1 * XDir.Y() + A2 * YDir.Y() + A3 * ZDir.Y() + PLoc.Y(),
                A1 * XDir.Z() + A2 * YDir.Z() + A3 * ZDir.Z() + PLoc.Z());
}

gp_Pnt ElSLib::TorusValue(const double  U,
                          const double  V,
                          const gp_Ax3& Pos,
                          const double  MajorRadius,
                          const double  MinorRadius)
{

  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        R    = MajorRadius + MinorRadius * cos(V);
  double        A3   = MinorRadius * sin(V);
  double        A1   = R * cos(U);
  double        A2   = R * sin(U);

  double eps = 10. * (MinorRadius + MajorRadius) * RealEpsilon();

  if (std::abs(A1) <= eps)
    A1 = 0.;

  if (std::abs(A2) <= eps)
    A2 = 0.;

  if (std::abs(A3) <= eps)
    A3 = 0.;

  return gp_Pnt(A1 * XDir.X() + A2 * YDir.X() + A3 * ZDir.X() + PLoc.X(),
                A1 * XDir.Y() + A2 * YDir.Y() + A3 * ZDir.Y() + PLoc.Y(),
                A1 * XDir.Z() + A2 * YDir.Z() + A3 * ZDir.Z() + PLoc.Z());
}

gp_Vec ElSLib::PlaneDN(const double, const double, const gp_Ax3& Pos, const int Nu, const int Nv)
{
  if (Nu == 0 && Nv == 1)
  {
    return gp_Vec(Pos.YDirection());
  }
  else if (Nu == 1 && Nv == 0)
  {
    return gp_Vec(Pos.XDirection());
  }
  return gp_Vec(0., 0., 0.);
}

gp_Vec ElSLib::ConeDN(const double  U,
                      const double  V,
                      const gp_Ax3& Pos,
                      const double  Radius,
                      const double  SAngle,
                      const int     Nu,
                      const int     Nv)
{
  gp_XYZ Xdir = Pos.XDirection().XYZ();
  gp_XYZ Ydir = Pos.YDirection().XYZ();
  double Um   = U + Nu * M_PI_2;
  Xdir.Multiply(cos(Um));
  Ydir.Multiply(sin(Um));
  Xdir.Add(Ydir);
  if (Nv == 0)
  {
    Xdir.Multiply(Radius + V * sin(SAngle));
    if (Nu == 0)
      Xdir.Add(Pos.Location().XYZ());
    return gp_Vec(Xdir);
  }
  else if (Nv == 1)
  {
    Xdir.Multiply(sin(SAngle));
    if (Nu == 0)
      Xdir.Add(Pos.Direction().XYZ() * cos(SAngle));
    return gp_Vec(Xdir);
  }
  return gp_Vec(0.0, 0.0, 0.0);
}

gp_Vec ElSLib::CylinderDN(const double U,
                          const double,
                          const gp_Ax3& Pos,
                          const double  Radius,
                          const int     Nu,
                          const int     Nv)
{
  if (Nu + Nv < 1 || Nu < 0 || Nv < 0)
  {
    return gp_Vec();
  }
  if (Nv == 0)
  {
    double RCosU = Radius * cos(U);
    double RSinU = Radius * sin(U);
    gp_XYZ Xdir  = Pos.XDirection().XYZ();
    gp_XYZ Ydir  = Pos.YDirection().XYZ();
    if ((Nu + 6) % 4 == 0)
    {
      Xdir.Multiply(-RCosU);
      Ydir.Multiply(-RSinU);
    }
    else if ((Nu + 5) % 4 == 0)
    {
      Xdir.Multiply(RSinU);
      Ydir.Multiply(-RCosU);
    }
    else if ((Nu + 3) % 4 == 0)
    {
      Xdir.Multiply(-RSinU);
      Ydir.Multiply(RCosU);
    }
    else if (Nu % 4 == 0)
    {
      Xdir.Multiply(RCosU);
      Ydir.Multiply(RSinU);
    }
    Xdir.Add(Ydir);
    return gp_Vec(Xdir);
  }
  else if (Nv == 1 && Nu == 0)
  {
    return gp_Vec(Pos.Direction());
  }
  else
  {
    return gp_Vec(0.0, 0.0, 0.0);
  }
}

gp_Vec ElSLib::SphereDN(const double  U,
                        const double  V,
                        const gp_Ax3& Pos,
                        const double  Radius,
                        const int     Nu,
                        const int     Nv)
{
  if (Nu + Nv < 1 || Nu < 0 || Nv < 0)
  {
    return gp_Vec();
  }
  double        CosU  = cos(U);
  double        SinU  = sin(U);
  double        RCosV = Radius * cos(V);
  const gp_XYZ& XDir  = Pos.XDirection().XYZ();
  const gp_XYZ& YDir  = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir  = Pos.Direction().XYZ();
  double        A1, A2, A3, X, Y, Z;
  if (Nu == 0)
  {
    double RSinV = Radius * sin(V);
    if (IsOdd(Nv))
    {
      A1 = -RSinV * CosU;
      A2 = -RSinV * SinU;
      A3 = RCosV;
    }
    else
    {
      A1 = -RCosV * CosU;
      A2 = -RCosV * SinU;
      A3 = -RSinV;
    }
    X = A1 * XDir.X() + A2 * YDir.X() + A3 * ZDir.X();
    Y = A1 * XDir.Y() + A2 * YDir.Y() + A3 * ZDir.Y();
    Z = A1 * XDir.Z() + A2 * YDir.Z() + A3 * ZDir.Z();
    if ((Nv + 2) % 4 != 0 && (Nv + 3) % 4 != 0)
    {
      X = -X;
      Y = -Y;
      Z = -Z;
    }
  }
  else if (Nv == 0)
  {
    if (IsOdd(Nu))
    {
      A1 = -RCosV * SinU;
      A2 = RCosV * CosU;
    }
    else
    {
      A1 = RCosV * CosU;
      A2 = RCosV * SinU;
    }
    X = A1 * XDir.X() + A2 * YDir.X();
    Y = A1 * XDir.Y() + A2 * YDir.Y();
    Z = A1 * XDir.Z() + A2 * YDir.Z();
    if ((Nu + 2) % 4 == 0 || (Nu + 1) % 4 == 0)
    {
      X = -X;
      Y = -Y;
      Z = -Z;
    }
  }
  else
  {
    double RSinV = Radius * sin(V);
    if (IsOdd(Nu))
    {
      A1 = -SinU;
      A2 = CosU;
    }
    else
    {
      A1 = -CosU;
      A2 = -SinU;
    }
    if (IsOdd(Nv))
      A3 = -RSinV;
    else
      A3 = -RCosV;
    X = (A1 * XDir.X() + A2 * YDir.X()) * A3;
    Y = (A1 * XDir.Y() + A2 * YDir.Y()) * A3;
    Z = (A1 * XDir.Z() + A2 * YDir.Z()) * A3;
    if (((Nu + 2) % 4 != 0 && (Nu + 3) % 4 != 0 && ((Nv + 2) % 4 == 0 || (Nv + 3) % 4 == 0))
        || (((Nu + 2) % 4 == 0 || (Nu + 3) % 4 == 0) && (Nv + 2) % 4 != 0 && (Nv + 3) % 4 != 0))
    {
      X = -X;
      Y = -Y;
      Z = -Z;
    }
  }
  return gp_Vec(X, Y, Z);
}

gp_Vec ElSLib::TorusDN(const double  U,
                       const double  V,
                       const gp_Ax3& Pos,
                       const double  MajorRadius,
                       const double  MinorRadius,
                       const int     Nu,
                       const int     Nv)
{
  if (Nu + Nv < 1 || Nu < 0 || Nv < 0)
  {
    return gp_Vec();
  }
  double        CosU = cos(U);
  double        SinU = sin(U);
  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  double        A1, A2, A3, X = 0, Y = 0, Z = 0;

  double eps = 10. * (MinorRadius + MajorRadius) * RealEpsilon();

  if (Nv == 0)
  {
    double R = MajorRadius + MinorRadius * cos(V);
    if (IsOdd(Nu))
    {
      A1 = -R * SinU;
      A2 = R * CosU;
    }
    else
    {
      A1 = -R * CosU;
      A2 = -R * SinU;
    }

    if (std::abs(A1) <= eps)
      A1 = 0.;

    if (std::abs(A2) <= eps)
      A2 = 0.;

    X = A1 * XDir.X() + A2 * YDir.X();
    Y = A1 * XDir.Y() + A2 * YDir.Y();
    Z = A1 * XDir.Z() + A2 * YDir.Z();
    if ((Nu + 2) % 4 != 0 && (Nu + 3) % 4 != 0)
    {
      X = -X;
      Y = -Y;
      Z = -Z;
    }
  }
  else if (Nu == 0)
  {
    double RCosV = MinorRadius * cos(V);
    double RSinV = MinorRadius * sin(V);
    if (IsOdd(Nv))
    {
      A1 = -RSinV * CosU;
      A2 = -RSinV * SinU;
      A3 = RCosV;
    }
    else
    {
      A1 = -RCosV * CosU;
      A2 = -RCosV * SinU;
      A3 = -RSinV;
    }

    if (std::abs(A1) <= eps)
      A1 = 0.;

    if (std::abs(A2) <= eps)
      A2 = 0.;

    if (std::abs(A3) <= eps)
      A3 = 0.;

    X = A1 * XDir.X() + A2 * YDir.X() + A3 * ZDir.X();
    Y = A1 * XDir.Y() + A2 * YDir.Y() + A3 * ZDir.Y();
    Z = A1 * XDir.Z() + A2 * YDir.Z() + A3 * ZDir.Z();
    if ((Nv + 2) % 4 != 0 && (Nv + 3) % 4 != 0)
    {
      X = -X;
      Y = -Y;
      Z = -Z;
    }
  }
  else
  {
    if (IsOdd(Nu) && IsOdd(Nv))
    {
      double RSinV = MinorRadius * sin(V);
      A1           = RSinV * SinU;
      A2           = -RSinV * CosU;

      if (std::abs(A1) <= eps)
        A1 = 0.;

      if (std::abs(A2) <= eps)
        A2 = 0.;

      X = A1 * XDir.X() + A2 * YDir.X();
      Y = A1 * XDir.Y() + A2 * YDir.Y();
      Z = A1 * XDir.Z() + A2 * YDir.Z();
    }
    else if (IsEven(Nu) && IsEven(Nv))
    {
      double RCosV = MinorRadius * cos(V);
      A1           = RCosV * CosU;
      A2           = RCosV * SinU;

      if (std::abs(A1) <= eps)
        A1 = 0.;

      if (std::abs(A2) <= eps)
        A2 = 0.;

      X = A1 * XDir.X() + A2 * YDir.X();
      Y = A1 * XDir.Y() + A2 * YDir.Y();
      Z = A1 * XDir.Z() + A2 * YDir.Z();
    }
    else if (IsEven(Nv) && IsOdd(Nu))
    {
      double RCosV = MinorRadius * cos(V);
      A1           = RCosV * SinU;
      A2           = -RCosV * CosU;

      if (std::abs(A1) <= eps)
        A1 = 0.;

      if (std::abs(A2) <= eps)
        A2 = 0.;

      X = A1 * XDir.X() + A2 * YDir.X();
      Y = A1 * XDir.Y() + A2 * YDir.Y();
      Z = A1 * XDir.Z() + A2 * YDir.Z();
      if (((Nv + Nu + 3) % 4) == 0)
      {
        X = -X;
        Y = -Y;
        Z = -Z;
      }
    }
    else if (IsOdd(Nv) && IsEven(Nu))
    {
      double RSinV = MinorRadius * sin(V);
      A1           = RSinV * CosU;
      A2           = RSinV * SinU;

      if (std::abs(A1) <= eps)
        A1 = 0.;

      if (std::abs(A2) <= eps)
        A2 = 0.;

      X = A1 * XDir.X() + A2 * YDir.X();
      Y = A1 * XDir.Y() + A2 * YDir.Y();
      Z = A1 * XDir.Z() + A2 * YDir.Z();
      if (((Nu + Nv + 3) % 4) == 0)
      {
        X = -X;
        Y = -Y;
        Z = -Z;
      }
    }
  }
  return gp_Vec(X, Y, Z);
}

void ElSLib::PlaneD0(const double U, const double V, const gp_Ax3& Pos, gp_Pnt& P)
{
  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  P.SetX(U * XDir.X() + V * YDir.X() + PLoc.X());
  P.SetY(U * XDir.Y() + V * YDir.Y() + PLoc.Y());
  P.SetZ(U * XDir.Z() + V * YDir.Z() + PLoc.Z());
}

void ElSLib::ConeD0(const double  U,
                    const double  V,
                    const gp_Ax3& Pos,
                    const double  Radius,
                    const double  SAngle,
                    gp_Pnt&       P)
{
  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        R    = Radius + V * sin(SAngle);
  double        A3   = V * cos(SAngle);
  double        A1   = R * cos(U);
  double        A2   = R * sin(U);
  P.SetX(A1 * XDir.X() + A2 * YDir.X() + A3 * ZDir.X() + PLoc.X());
  P.SetY(A1 * XDir.Y() + A2 * YDir.Y() + A3 * ZDir.Y() + PLoc.Y());
  P.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + A3 * ZDir.Z() + PLoc.Z());
}

void ElSLib::CylinderD0(const double  U,
                        const double  V,
                        const gp_Ax3& Pos,
                        const double  Radius,
                        gp_Pnt&       P)
{
  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        A1   = Radius * cos(U);
  double        A2   = Radius * sin(U);
  P.SetX(A1 * XDir.X() + A2 * YDir.X() + V * ZDir.X() + PLoc.X());
  P.SetY(A1 * XDir.Y() + A2 * YDir.Y() + V * ZDir.Y() + PLoc.Y());
  P.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + V * ZDir.Z() + PLoc.Z());
}

void ElSLib::SphereD0(const double  U,
                      const double  V,
                      const gp_Ax3& Pos,
                      const double  Radius,
                      gp_Pnt&       P)
{
  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        R    = Radius * cos(V);
  double        A3   = Radius * sin(V);
  double        A1   = R * cos(U);
  double        A2   = R * sin(U);
  P.SetX(A1 * XDir.X() + A2 * YDir.X() + A3 * ZDir.X() + PLoc.X());
  P.SetY(A1 * XDir.Y() + A2 * YDir.Y() + A3 * ZDir.Y() + PLoc.Y());
  P.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + A3 * ZDir.Z() + PLoc.Z());
}

void ElSLib::TorusD0(const double  U,
                     const double  V,
                     const gp_Ax3& Pos,
                     const double  MajorRadius,
                     const double  MinorRadius,
                     gp_Pnt&       P)
{
  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        R    = MajorRadius + MinorRadius * cos(V);
  double        A3   = MinorRadius * sin(V);
  double        A1   = R * cos(U);
  double        A2   = R * sin(U);

  double eps = 10. * (MinorRadius + MajorRadius) * RealEpsilon();

  if (std::abs(A1) <= eps)
    A1 = 0.;

  if (std::abs(A2) <= eps)
    A2 = 0.;

  if (std::abs(A3) <= eps)
    A3 = 0.;

  P.SetX(A1 * XDir.X() + A2 * YDir.X() + A3 * ZDir.X() + PLoc.X());
  P.SetY(A1 * XDir.Y() + A2 * YDir.Y() + A3 * ZDir.Y() + PLoc.Y());
  P.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + A3 * ZDir.Z() + PLoc.Z());
}

void ElSLib::PlaneD1(const double  U,
                     const double  V,
                     const gp_Ax3& Pos,
                     gp_Pnt&       P,
                     gp_Vec&       Vu,
                     gp_Vec&       Vv)
{
  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  P.SetX(U * XDir.X() + V * YDir.X() + PLoc.X());
  P.SetY(U * XDir.Y() + V * YDir.Y() + PLoc.Y());
  P.SetZ(U * XDir.Z() + V * YDir.Z() + PLoc.Z());
  Vu.SetX(XDir.X());
  Vu.SetY(XDir.Y());
  Vu.SetZ(XDir.Z());
  Vv.SetX(YDir.X());
  Vv.SetY(YDir.Y());
  Vv.SetZ(YDir.Z());
}

void ElSLib::ConeD1(const double  U,
                    const double  V,
                    const gp_Ax3& Pos,
                    const double  Radius,
                    const double  SAngle,
                    gp_Pnt&       P,
                    gp_Vec&       Vu,
                    gp_Vec&       Vv)
{

  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        CosU = cos(U);
  double        SinU = sin(U);
  double        CosA = cos(SAngle);
  double        SinA = sin(SAngle);
  double        R    = Radius + V * SinA;
  double        A3   = V * CosA;
  double        A1   = R * CosU;
  double        A2   = R * SinU;
  double        R1   = SinA * CosU;
  double        R2   = SinA * SinU;
  P.SetX(A1 * XDir.X() + A2 * YDir.X() + A3 * ZDir.X() + PLoc.X());
  P.SetY(A1 * XDir.Y() + A2 * YDir.Y() + A3 * ZDir.Y() + PLoc.Y());
  P.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + A3 * ZDir.Z() + PLoc.Z());
  Vu.SetX(-A2 * XDir.X() + A1 * YDir.X());
  Vu.SetY(-A2 * XDir.Y() + A1 * YDir.Y());
  Vu.SetZ(-A2 * XDir.Z() + A1 * YDir.Z());
  Vv.SetX(R1 * XDir.X() + R2 * YDir.X() + CosA * ZDir.X());
  Vv.SetY(R1 * XDir.Y() + R2 * YDir.Y() + CosA * ZDir.Y());
  Vv.SetZ(R1 * XDir.Z() + R2 * YDir.Z() + CosA * ZDir.Z());
}

void ElSLib::CylinderD1(const double  U,
                        const double  V,
                        const gp_Ax3& Pos,
                        const double  Radius,
                        gp_Pnt&       P,
                        gp_Vec&       Vu,
                        gp_Vec&       Vv)
{
  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        A1   = Radius * cos(U);
  double        A2   = Radius * sin(U);
  P.SetX(A1 * XDir.X() + A2 * YDir.X() + V * ZDir.X() + PLoc.X());
  P.SetY(A1 * XDir.Y() + A2 * YDir.Y() + V * ZDir.Y() + PLoc.Y());
  P.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + V * ZDir.Z() + PLoc.Z());
  Vu.SetX(-A2 * XDir.X() + A1 * YDir.X());
  Vu.SetY(-A2 * XDir.Y() + A1 * YDir.Y());
  Vu.SetZ(-A2 * XDir.Z() + A1 * YDir.Z());
  Vv.SetX(ZDir.X());
  Vv.SetY(ZDir.Y());
  Vv.SetZ(ZDir.Z());
}

void ElSLib::SphereD1(const double  U,
                      const double  V,
                      const gp_Ax3& Pos,
                      const double  Radius,
                      gp_Pnt&       P,
                      gp_Vec&       Vu,
                      gp_Vec&       Vv)
{

  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        CosU = cos(U);
  double        SinU = sin(U);
  double        R1   = Radius * cos(V);
  double        R2   = Radius * sin(V);
  double        A1   = R1 * CosU;
  double        A2   = R1 * SinU;
  double        A3   = R2 * CosU;
  double        A4   = R2 * SinU;
  P.SetX(A1 * XDir.X() + A2 * YDir.X() + R2 * ZDir.X() + PLoc.X());
  P.SetY(A1 * XDir.Y() + A2 * YDir.Y() + R2 * ZDir.Y() + PLoc.Y());
  P.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + R2 * ZDir.Z() + PLoc.Z());
  Vu.SetX(-A2 * XDir.X() + A1 * YDir.X());
  Vu.SetY(-A2 * XDir.Y() + A1 * YDir.Y());
  Vu.SetZ(-A2 * XDir.Z() + A1 * YDir.Z());
  Vv.SetX(-A3 * XDir.X() - A4 * YDir.X() + R1 * ZDir.X());
  Vv.SetY(-A3 * XDir.Y() - A4 * YDir.Y() + R1 * ZDir.Y());
  Vv.SetZ(-A3 * XDir.Z() - A4 * YDir.Z() + R1 * ZDir.Z());
}

void ElSLib::TorusD1(const double  U,
                     const double  V,
                     const gp_Ax3& Pos,
                     const double  MajorRadius,
                     const double  MinorRadius,
                     gp_Pnt&       P,
                     gp_Vec&       Vu,
                     gp_Vec&       Vv)
{

  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        CosU = cos(U);
  double        SinU = sin(U);
  double        R1   = MinorRadius * cos(V);
  double        R2   = MinorRadius * sin(V);
  double        R    = MajorRadius + R1;
  double        A1   = R * CosU;
  double        A2   = R * SinU;
  double        A3   = R2 * CosU;
  double        A4   = R2 * SinU;

  double eps = 10. * (MinorRadius + MajorRadius) * RealEpsilon();

  if (std::abs(A1) <= eps)
    A1 = 0.;

  if (std::abs(A2) <= eps)
    A2 = 0.;

  if (std::abs(A3) <= eps)
    A3 = 0.;

  if (std::abs(A4) <= eps)
    A4 = 0.;

  P.SetX(A1 * XDir.X() + A2 * YDir.X() + R2 * ZDir.X() + PLoc.X());
  P.SetY(A1 * XDir.Y() + A2 * YDir.Y() + R2 * ZDir.Y() + PLoc.Y());
  P.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + R2 * ZDir.Z() + PLoc.Z());
  Vu.SetX(-A2 * XDir.X() + A1 * YDir.X());
  Vu.SetY(-A2 * XDir.Y() + A1 * YDir.Y());
  Vu.SetZ(-A2 * XDir.Z() + A1 * YDir.Z());
  Vv.SetX(-A3 * XDir.X() - A4 * YDir.X() + R1 * ZDir.X());
  Vv.SetY(-A3 * XDir.Y() - A4 * YDir.Y() + R1 * ZDir.Y());
  Vv.SetZ(-A3 * XDir.Z() - A4 * YDir.Z() + R1 * ZDir.Z());
}

void ElSLib::ConeD2(const double  U,
                    const double  V,
                    const gp_Ax3& Pos,
                    const double  Radius,
                    const double  SAngle,
                    gp_Pnt&       P,
                    gp_Vec&       Vu,
                    gp_Vec&       Vv,
                    gp_Vec&       Vuu,
                    gp_Vec&       Vvv,
                    gp_Vec&       Vuv)
{

  const gp_XYZ& XDir  = Pos.XDirection().XYZ();
  const gp_XYZ& YDir  = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir  = Pos.Direction().XYZ();
  const gp_XYZ& PLoc  = Pos.Location().XYZ();
  double        CosU  = cos(U);
  double        SinU  = sin(U);
  double        CosA  = cos(SAngle);
  double        SinA  = sin(SAngle);
  double        R     = Radius + V * SinA;
  double        A3    = V * CosA;
  double        A1    = R * CosU;
  double        A2    = R * SinU;
  double        R1    = SinA * CosU;
  double        R2    = SinA * SinU;
  double        Som1X = A1 * XDir.X() + A2 * YDir.X();
  double        Som1Y = A1 * XDir.Y() + A2 * YDir.Y();
  double        Som1Z = A1 * XDir.Z() + A2 * YDir.Z();
  P.SetX(Som1X + A3 * ZDir.X() + PLoc.X());
  P.SetY(Som1Y + A3 * ZDir.Y() + PLoc.Y());
  P.SetZ(Som1Z + A3 * ZDir.Z() + PLoc.Z());
  Vu.SetX(-A2 * XDir.X() + A1 * YDir.X());
  Vu.SetY(-A2 * XDir.Y() + A1 * YDir.Y());
  Vu.SetZ(-A2 * XDir.Z() + A1 * YDir.Z());
  Vv.SetX(R1 * XDir.X() + R2 * YDir.X() + CosA * ZDir.X());
  Vv.SetY(R1 * XDir.Y() + R2 * YDir.Y() + CosA * ZDir.Y());
  Vv.SetZ(R1 * XDir.Z() + R2 * YDir.Z() + CosA * ZDir.Z());
  Vuu.SetX(-Som1X);
  Vuu.SetY(-Som1Y);
  Vuu.SetZ(-Som1Z);
  Vvv.SetX(0.0);
  Vvv.SetY(0.0);
  Vvv.SetZ(0.0);
  Vuv.SetX(-R2 * XDir.X() + R1 * YDir.X());
  Vuv.SetY(-R2 * XDir.Y() + R1 * YDir.Y());
  Vuv.SetZ(-R2 * XDir.Z() + R1 * YDir.Z());
}

void ElSLib::CylinderD2(const double  U,
                        const double  V,
                        const gp_Ax3& Pos,
                        const double  Radius,
                        gp_Pnt&       P,
                        gp_Vec&       Vu,
                        gp_Vec&       Vv,
                        gp_Vec&       Vuu,
                        gp_Vec&       Vvv,
                        gp_Vec&       Vuv)
{
  const gp_XYZ& XDir  = Pos.XDirection().XYZ();
  const gp_XYZ& YDir  = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir  = Pos.Direction().XYZ();
  const gp_XYZ& PLoc  = Pos.Location().XYZ();
  double        A1    = Radius * cos(U);
  double        A2    = Radius * sin(U);
  double        Som1X = A1 * XDir.X() + A2 * YDir.X();
  double        Som1Y = A1 * XDir.Y() + A2 * YDir.Y();
  double        Som1Z = A1 * XDir.Z() + A2 * YDir.Z();
  P.SetX(Som1X + V * ZDir.X() + PLoc.X());
  P.SetY(Som1Y + V * ZDir.Y() + PLoc.Y());
  P.SetZ(Som1Z + V * ZDir.Z() + PLoc.Z());
  Vu.SetX(-A2 * XDir.X() + A1 * YDir.X());
  Vu.SetY(-A2 * XDir.Y() + A1 * YDir.Y());
  Vu.SetZ(-A2 * XDir.Z() + A1 * YDir.Z());
  Vv.SetX(ZDir.X());
  Vv.SetY(ZDir.Y());
  Vv.SetZ(ZDir.Z());
  Vuu.SetX(-Som1X);
  Vuu.SetY(-Som1Y);
  Vuu.SetZ(-Som1Z);
  Vvv.SetX(0.0);
  Vvv.SetY(0.0);
  Vvv.SetZ(0.0);
  Vuv.SetX(0.0);
  Vuv.SetY(0.0);
  Vuv.SetZ(0.0);
}

void ElSLib::SphereD2(const double  U,
                      const double  V,
                      const gp_Ax3& Pos,
                      const double  Radius,
                      gp_Pnt&       P,
                      gp_Vec&       Vu,
                      gp_Vec&       Vv,
                      gp_Vec&       Vuu,
                      gp_Vec&       Vvv,
                      gp_Vec&       Vuv)
{

  const gp_XYZ& XDir  = Pos.XDirection().XYZ();
  const gp_XYZ& YDir  = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir  = Pos.Direction().XYZ();
  const gp_XYZ& PLoc  = Pos.Location().XYZ();
  double        CosU  = cos(U);
  double        SinU  = sin(U);
  double        R1    = Radius * cos(V);
  double        R2    = Radius * sin(V);
  double        A1    = R1 * CosU;
  double        A2    = R1 * SinU;
  double        A3    = R2 * CosU;
  double        A4    = R2 * SinU;
  double        Som1X = A1 * XDir.X() + A2 * YDir.X();
  double        Som1Y = A1 * XDir.Y() + A2 * YDir.Y();
  double        Som1Z = A1 * XDir.Z() + A2 * YDir.Z();
  double        R2ZX  = R2 * ZDir.X();
  double        R2ZY  = R2 * ZDir.Y();
  double        R2ZZ  = R2 * ZDir.Z();
  P.SetX(Som1X + R2ZX + PLoc.X());
  P.SetY(Som1Y + R2ZY + PLoc.Y());
  P.SetZ(Som1Z + R2ZZ + PLoc.Z());
  Vu.SetX(-A2 * XDir.X() + A1 * YDir.X());
  Vu.SetY(-A2 * XDir.Y() + A1 * YDir.Y());
  Vu.SetZ(-A2 * XDir.Z() + A1 * YDir.Z());
  Vv.SetX(-A3 * XDir.X() - A4 * YDir.X() + R1 * ZDir.X());
  Vv.SetY(-A3 * XDir.Y() - A4 * YDir.Y() + R1 * ZDir.Y());
  Vv.SetZ(-A3 * XDir.Z() - A4 * YDir.Z() + R1 * ZDir.Z());
  Vuu.SetX(-Som1X);
  Vuu.SetY(-Som1Y);
  Vuu.SetZ(-Som1Z);
  Vvv.SetX(-Som1X - R2ZX);
  Vvv.SetY(-Som1Y - R2ZY);
  Vvv.SetZ(-Som1Z - R2ZZ);
  Vuv.SetX(A4 * XDir.X() - A3 * YDir.X());
  Vuv.SetY(A4 * XDir.Y() - A3 * YDir.Y());
  Vuv.SetZ(A4 * XDir.Z() - A3 * YDir.Z());
}

void ElSLib::TorusD2(const double  U,
                     const double  V,
                     const gp_Ax3& Pos,
                     const double  MajorRadius,
                     const double  MinorRadius,
                     gp_Pnt&       P,
                     gp_Vec&       Vu,
                     gp_Vec&       Vv,
                     gp_Vec&       Vuu,
                     gp_Vec&       Vvv,
                     gp_Vec&       Vuv)
{

  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        CosU = cos(U);
  double        SinU = sin(U);
  double        R1   = MinorRadius * cos(V);
  double        R2   = MinorRadius * sin(V);
  double        R    = MajorRadius + R1;
  double        A1   = R * CosU;
  double        A2   = R * SinU;
  double        A3   = R2 * CosU;
  double        A4   = R2 * SinU;
  double        A5   = R1 * CosU;
  double        A6   = R1 * SinU;

  double eps = 10. * (MinorRadius + MajorRadius) * RealEpsilon();

  if (std::abs(A1) <= eps)
    A1 = 0.;

  if (std::abs(A2) <= eps)
    A2 = 0.;

  if (std::abs(A3) <= eps)
    A3 = 0.;

  if (std::abs(A4) <= eps)
    A4 = 0.;

  if (std::abs(A5) <= eps)
    A5 = 0.;

  if (std::abs(A6) <= eps)
    A6 = 0.;

  double Som1X = A1 * XDir.X() + A2 * YDir.X();
  double Som1Y = A1 * XDir.Y() + A2 * YDir.Y();
  double Som1Z = A1 * XDir.Z() + A2 * YDir.Z();
  double R2ZX  = R2 * ZDir.X();
  double R2ZY  = R2 * ZDir.Y();
  double R2ZZ  = R2 * ZDir.Z();
  P.SetX(Som1X + R2ZX + PLoc.X());
  P.SetY(Som1Y + R2ZY + PLoc.Y());
  P.SetZ(Som1Z + R2ZZ + PLoc.Z());
  Vu.SetX(-A2 * XDir.X() + A1 * YDir.X());
  Vu.SetY(-A2 * XDir.Y() + A1 * YDir.Y());
  Vu.SetZ(-A2 * XDir.Z() + A1 * YDir.Z());
  Vv.SetX(-A3 * XDir.X() - A4 * YDir.X() + R1 * ZDir.X());
  Vv.SetY(-A3 * XDir.Y() - A4 * YDir.Y() + R1 * ZDir.Y());
  Vv.SetZ(-A3 * XDir.Z() - A4 * YDir.Z() + R1 * ZDir.Z());
  Vuu.SetX(-Som1X);
  Vuu.SetY(-Som1Y);
  Vuu.SetZ(-Som1Z);
  Vvv.SetX(-A5 * XDir.X() - A6 * YDir.X() - R2ZX);
  Vvv.SetY(-A5 * XDir.Y() - A6 * YDir.Y() - R2ZY);
  Vvv.SetZ(-A5 * XDir.Z() - A6 * YDir.Z() - R2ZZ);
  Vuv.SetX(A4 * XDir.X() - A3 * YDir.X());
  Vuv.SetY(A4 * XDir.Y() - A3 * YDir.Y());
  Vuv.SetZ(A4 * XDir.Z() - A3 * YDir.Z());
}

void ElSLib::ConeD3(const double  U,
                    const double  V,
                    const gp_Ax3& Pos,
                    const double  Radius,
                    const double  SAngle,
                    gp_Pnt&       P,
                    gp_Vec&       Vu,
                    gp_Vec&       Vv,
                    gp_Vec&       Vuu,
                    gp_Vec&       Vvv,
                    gp_Vec&       Vuv,
                    gp_Vec&       Vuuu,
                    gp_Vec&       Vvvv,
                    gp_Vec&       Vuuv,
                    gp_Vec&       Vuvv)
{

  const gp_XYZ& XDir  = Pos.XDirection().XYZ();
  const gp_XYZ& YDir  = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir  = Pos.Direction().XYZ();
  const gp_XYZ& PLoc  = Pos.Location().XYZ();
  double        CosU  = cos(U);
  double        SinU  = sin(U);
  double        CosA  = cos(SAngle);
  double        SinA  = sin(SAngle);
  double        R     = Radius + V * SinA;
  double        A3    = V * CosA;
  double        A1    = R * CosU;
  double        A2    = R * SinU;
  double        R1    = SinA * CosU;
  double        R2    = SinA * SinU;
  double        Som1X = A1 * XDir.X() + A2 * YDir.X();
  double        Som1Y = A1 * XDir.Y() + A2 * YDir.Y();
  double        Som1Z = A1 * XDir.Z() + A2 * YDir.Z();
  double        Som2X = R1 * XDir.X() + R2 * YDir.X();
  double        Som2Y = R1 * XDir.Y() + R2 * YDir.Y();
  double        Som2Z = R1 * XDir.Z() + R2 * YDir.Z();
  double        Dif1X = A2 * XDir.X() - A1 * YDir.X();
  double        Dif1Y = A2 * XDir.Y() - A1 * YDir.Y();
  double        Dif1Z = A2 * XDir.Z() - A1 * YDir.Z();
  P.SetX(Som1X + A3 * ZDir.X() + PLoc.X());
  P.SetY(Som1Y + A3 * ZDir.Y() + PLoc.Y());
  P.SetZ(Som1Z + A3 * ZDir.Z() + PLoc.Z());
  Vu.SetX(-Dif1X);
  Vu.SetY(-Dif1Y);
  Vu.SetZ(-Dif1Z);
  Vv.SetX(Som2X + CosA * ZDir.X());
  Vv.SetY(Som2Y + CosA * ZDir.Y());
  Vv.SetZ(Som2Z + CosA * ZDir.Z());
  Vuu.SetX(-Som1X);
  Vuu.SetY(-Som1Y);
  Vuu.SetZ(-Som1Z);
  Vvv.SetX(0.0);
  Vvv.SetY(0.0);
  Vvv.SetZ(0.0);
  Vuv.SetX(-R2 * XDir.X() + R1 * YDir.X());
  Vuv.SetY(-R2 * XDir.Y() + R1 * YDir.Y());
  Vuv.SetZ(-R2 * XDir.Z() + R1 * YDir.Z());
  Vuuu.SetX(Dif1X);
  Vuuu.SetY(Dif1Y);
  Vuuu.SetZ(Dif1Z);
  Vvvv.SetX(0.0);
  Vvvv.SetY(0.0);
  Vvvv.SetZ(0.0);
  Vuvv.SetX(0.0);
  Vuvv.SetY(0.0);
  Vuvv.SetZ(0.0);
  Vuuv.SetX(-Som2X);
  Vuuv.SetY(-Som2Y);
  Vuuv.SetZ(-Som2Z);
}

void ElSLib::CylinderD3(const double  U,
                        const double  V,
                        const gp_Ax3& Pos,
                        const double  Radius,
                        gp_Pnt&       P,
                        gp_Vec&       Vu,
                        gp_Vec&       Vv,
                        gp_Vec&       Vuu,
                        gp_Vec&       Vvv,
                        gp_Vec&       Vuv,
                        gp_Vec&       Vuuu,
                        gp_Vec&       Vvvv,
                        gp_Vec&       Vuuv,
                        gp_Vec&       Vuvv)
{
  const gp_XYZ& XDir  = Pos.XDirection().XYZ();
  const gp_XYZ& YDir  = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir  = Pos.Direction().XYZ();
  const gp_XYZ& PLoc  = Pos.Location().XYZ();
  double        A1    = Radius * cos(U);
  double        A2    = Radius * sin(U);
  double        Som1X = A1 * XDir.X() + A2 * YDir.X();
  double        Som1Y = A1 * XDir.Y() + A2 * YDir.Y();
  double        Som1Z = A1 * XDir.Z() + A2 * YDir.Z();
  double        Dif1X = A2 * XDir.X() - A1 * YDir.X();
  double        Dif1Y = A2 * XDir.Y() - A1 * YDir.Y();
  double        Dif1Z = A2 * XDir.Z() - A1 * YDir.Z();
  P.SetX(Som1X + V * ZDir.X() + PLoc.X());
  P.SetY(Som1Y + V * ZDir.Y() + PLoc.Y());
  P.SetZ(Som1Z + V * ZDir.Z() + PLoc.Z());
  Vu.SetX(-Dif1X);
  Vu.SetY(-Dif1Y);
  Vu.SetZ(-Dif1Z);
  Vv.SetX(ZDir.X());
  Vv.SetY(ZDir.Y());
  Vv.SetZ(ZDir.Z());
  Vuu.SetX(-Som1X);
  Vuu.SetY(-Som1Y);
  Vuu.SetZ(-Som1Z);
  Vvv.SetX(0.0);
  Vvv.SetY(0.0);
  Vvv.SetZ(0.0);
  Vuv.SetX(0.0);
  Vuv.SetY(0.0);
  Vuv.SetZ(0.0);
  Vuuu.SetX(Dif1X);
  Vuuu.SetY(Dif1Y);
  Vuuu.SetZ(Dif1Z);
  Vvvv.SetX(0.0);
  Vvvv.SetY(0.0);
  Vvvv.SetZ(0.0);
  Vuvv.SetX(0.0);
  Vuvv.SetY(0.0);
  Vuvv.SetZ(0.0);
  Vuuv.SetX(0.0);
  Vuuv.SetY(0.0);
  Vuuv.SetZ(0.0);
}

void ElSLib::SphereD3(const double  U,
                      const double  V,
                      const gp_Ax3& Pos,
                      const double  Radius,
                      gp_Pnt&       P,
                      gp_Vec&       Vu,
                      gp_Vec&       Vv,
                      gp_Vec&       Vuu,
                      gp_Vec&       Vvv,
                      gp_Vec&       Vuv,
                      gp_Vec&       Vuuu,
                      gp_Vec&       Vvvv,
                      gp_Vec&       Vuuv,
                      gp_Vec&       Vuvv)
{

  const gp_XYZ& XDir  = Pos.XDirection().XYZ();
  const gp_XYZ& YDir  = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir  = Pos.Direction().XYZ();
  const gp_XYZ& PLoc  = Pos.Location().XYZ();
  double        CosU  = cos(U);
  double        SinU  = sin(U);
  double        R1    = Radius * cos(V);
  double        R2    = Radius * sin(V);
  double        A1    = R1 * CosU;
  double        A2    = R1 * SinU;
  double        A3    = R2 * CosU;
  double        A4    = R2 * SinU;
  double        Som1X = A1 * XDir.X() + A2 * YDir.X();
  double        Som1Y = A1 * XDir.Y() + A2 * YDir.Y();
  double        Som1Z = A1 * XDir.Z() + A2 * YDir.Z();
  double        Som3X = A3 * XDir.X() + A4 * YDir.X();
  double        Som3Y = A3 * XDir.Y() + A4 * YDir.Y();
  double        Som3Z = A3 * XDir.Z() + A4 * YDir.Z();
  double        Dif1X = A2 * XDir.X() - A1 * YDir.X();
  double        Dif1Y = A2 * XDir.Y() - A1 * YDir.Y();
  double        Dif1Z = A2 * XDir.Z() - A1 * YDir.Z();
  double        R1ZX  = R1 * ZDir.X();
  double        R1ZY  = R1 * ZDir.Y();
  double        R1ZZ  = R1 * ZDir.Z();
  double        R2ZX  = R2 * ZDir.X();
  double        R2ZY  = R2 * ZDir.Y();
  double        R2ZZ  = R2 * ZDir.Z();
  P.SetX(Som1X + R2ZX + PLoc.X());
  P.SetY(Som1Y + R2ZY + PLoc.Y());
  P.SetZ(Som1Z + R2ZZ + PLoc.Z());
  Vu.SetX(-Dif1X);
  Vu.SetY(-Dif1Y);
  Vu.SetZ(-Dif1Z);
  Vv.SetX(-Som3X + R1ZX);
  Vv.SetY(-Som3Y + R1ZY);
  Vv.SetZ(-Som3Z + R1ZZ);
  Vuu.SetX(-Som1X);
  Vuu.SetY(-Som1Y);
  Vuu.SetZ(-Som1Z);
  Vvv.SetX(-Som1X - R2ZX);
  Vvv.SetY(-Som1Y - R2ZY);
  Vvv.SetZ(-Som1Z - R2ZZ);
  Vuv.SetX(A4 * XDir.X() - A3 * YDir.X());
  Vuv.SetY(A4 * XDir.Y() - A3 * YDir.Y());
  Vuv.SetZ(A4 * XDir.Z() - A3 * YDir.Z());
  Vuuu.SetX(Dif1X);
  Vuuu.SetY(Dif1Y);
  Vuuu.SetZ(Dif1Z);
  Vvvv.SetX(Som3X - R1ZX);
  Vvvv.SetY(Som3Y - R1ZY);
  Vvvv.SetZ(Som3Z - R1ZZ);
  Vuvv.SetX(Dif1X);
  Vuvv.SetY(Dif1Y);
  Vuvv.SetZ(Dif1Z);
  Vuuv.SetX(Som3X);
  Vuuv.SetY(Som3Y);
  Vuuv.SetZ(Som3Z);
}

void ElSLib::TorusD3(const double  U,
                     const double  V,
                     const gp_Ax3& Pos,
                     const double  MajorRadius,
                     const double  MinorRadius,
                     gp_Pnt&       P,
                     gp_Vec&       Vu,
                     gp_Vec&       Vv,
                     gp_Vec&       Vuu,
                     gp_Vec&       Vvv,
                     gp_Vec&       Vuv,
                     gp_Vec&       Vuuu,
                     gp_Vec&       Vvvv,
                     gp_Vec&       Vuuv,
                     gp_Vec&       Vuvv)
{

  const gp_XYZ& XDir = Pos.XDirection().XYZ();
  const gp_XYZ& YDir = Pos.YDirection().XYZ();
  const gp_XYZ& ZDir = Pos.Direction().XYZ();
  const gp_XYZ& PLoc = Pos.Location().XYZ();
  double        CosU = cos(U);
  double        SinU = sin(U);
  double        R1   = MinorRadius * cos(V);
  double        R2   = MinorRadius * sin(V);
  double        R    = MajorRadius + R1;
  double        A1   = R * CosU;
  double        A2   = R * SinU;
  double        A3   = R2 * CosU;
  double        A4   = R2 * SinU;
  double        A5   = R1 * CosU;
  double        A6   = R1 * SinU;

  double eps = 10. * (MinorRadius + MajorRadius) * RealEpsilon();

  if (std::abs(A1) <= eps)
    A1 = 0.;

  if (std::abs(A2) <= eps)
    A2 = 0.;

  if (std::abs(A3) <= eps)
    A3 = 0.;

  if (std::abs(A4) <= eps)
    A4 = 0.;

  if (std::abs(A5) <= eps)
    A5 = 0.;

  if (std::abs(A6) <= eps)
    A6 = 0.;

  double Som1X = A1 * XDir.X() + A2 * YDir.X();
  double Som1Y = A1 * XDir.Y() + A2 * YDir.Y();
  double Som1Z = A1 * XDir.Z() + A2 * YDir.Z();
  double Som3X = A3 * XDir.X() + A4 * YDir.X();
  double Som3Y = A3 * XDir.Y() + A4 * YDir.Y();
  double Som3Z = A3 * XDir.Z() + A4 * YDir.Z();
  double Dif1X = A2 * XDir.X() - A1 * YDir.X();
  double Dif1Y = A2 * XDir.Y() - A1 * YDir.Y();
  double Dif1Z = A2 * XDir.Z() - A1 * YDir.Z();
  double R1ZX  = R1 * ZDir.X();
  double R1ZY  = R1 * ZDir.Y();
  double R1ZZ  = R1 * ZDir.Z();
  double R2ZX  = R2 * ZDir.X();
  double R2ZY  = R2 * ZDir.Y();
  double R2ZZ  = R2 * ZDir.Z();
  P.SetX(Som1X + R2ZX + PLoc.X());
  P.SetY(Som1Y + R2ZY + PLoc.Y());
  P.SetZ(Som1Z + R2ZZ + PLoc.Z());
  Vu.SetX(-Dif1X);
  Vu.SetY(-Dif1Y);
  Vu.SetZ(-Dif1Z);
  Vv.SetX(-Som3X + R1ZX);
  Vv.SetY(-Som3Y + R1ZY);
  Vv.SetZ(-Som3Z + R1ZZ);
  Vuu.SetX(-Som1X);
  Vuu.SetY(-Som1Y);
  Vuu.SetZ(-Som1Z);
  Vvv.SetX(-A5 * XDir.X() - A6 * YDir.X() - R2ZX);
  Vvv.SetY(-A5 * XDir.Y() - A6 * YDir.Y() - R2ZY);
  Vvv.SetZ(-A5 * XDir.Z() - A6 * YDir.Z() - R2ZZ);
  Vuv.SetX(A4 * XDir.X() - A3 * YDir.X());
  Vuv.SetY(A4 * XDir.Y() - A3 * YDir.Y());
  Vuv.SetZ(A4 * XDir.Z() - A3 * YDir.Z());
  Vuuu.SetX(Dif1X);
  Vuuu.SetY(Dif1Y);
  Vuuu.SetZ(Dif1Z);
  Vvvv.SetX(Som3X - R1ZX);
  Vvvv.SetY(Som3Y - R1ZY);
  Vvvv.SetZ(Som3Z - R1ZZ);
  Vuuv.SetX(Som3X);
  Vuuv.SetY(Som3Y);
  Vuuv.SetZ(Som3Z);
  Vuvv.SetX(A6 * XDir.X() - A5 * YDir.X());
  Vuvv.SetY(A6 * XDir.Y() - A5 * YDir.Y());
  Vuvv.SetZ(A6 * XDir.Z() - A5 * YDir.Z());
}

void ElSLib::PlaneParameters(const gp_Ax3& Pos, const gp_Pnt& P, double& U, double& V)
{
  gp_Trsf T;
  T.SetTransformation(Pos);
  gp_Pnt Ploc = P.Transformed(T);
  U           = Ploc.X();
  V           = Ploc.Y();
}

void ElSLib::CylinderParameters(const gp_Ax3& Pos,
                                const double,
                                const gp_Pnt& P,
                                double&       U,
                                double&       V)
{
  gp_Trsf T;
  T.SetTransformation(Pos);
  gp_Pnt Ploc = P.Transformed(T);
  U           = atan2(Ploc.Y(), Ploc.X());
  normalizeAngle(U);
  V = Ploc.Z();
}

void ElSLib::ConeParameters(const gp_Ax3& Pos,
                            const double  Radius,
                            const double  SAngle,
                            const gp_Pnt& P,
                            double&       U,
                            double&       V)
{
  gp_Trsf T;
  T.SetTransformation(Pos);
  gp_Pnt Ploc = P.Transformed(T);

  if (std::abs(Ploc.X()) < gp::Resolution() && std::abs(Ploc.Y()) < gp::Resolution())
  {
    U = 0.0;
  }
  else if (-Radius > Ploc.Z() * std::tan(SAngle))
  {

    U = atan2(-Ploc.Y(), -Ploc.X());
  }
  else
  {
    U = atan2(Ploc.Y(), Ploc.X());
  }
  normalizeAngle(U);

  V = sin(SAngle) * (Ploc.X() * cos(U) + Ploc.Y() * sin(U) - Radius) + cos(SAngle) * Ploc.Z();
}

void ElSLib::SphereParameters(const gp_Ax3& Pos,
                              const double,
                              const gp_Pnt& P,
                              double&       U,
                              double&       V)
{
  gp_Trsf T;
  T.SetTransformation(Pos);
  gp_Pnt Ploc = P.Transformed(T);
  double x, y, z;
  Ploc.Coord(x, y, z);
  double l = sqrt(x * x + y * y);
  if (l < gp::Resolution())
  {
    if (z > 0.)
      V = M_PI_2;
    else
      V = -M_PI_2;
    U = 0.;
  }
  else
  {
    V = atan(z / l);
    U = atan2(y, x);
    normalizeAngle(U);
  }
}

void ElSLib::TorusParameters(const gp_Ax3& Pos,
                             const double  MajorRadius,
                             const double  MinorRadius,
                             const gp_Pnt& P,
                             double&       U,
                             double&       V)
{
  gp_Trsf Tref;
  Tref.SetTransformation(Pos);
  gp_Pnt Ploc = P.Transformed(Tref);
  double x, y, z;
  Ploc.Coord(x, y, z);

  U = atan2(y, x);
  if (MajorRadius < MinorRadius)
  {
    const double cosu  = cos(U);
    const double sinu  = sin(U);
    const double z2    = z * z;
    const double MinR2 = MinorRadius * MinorRadius;
    const double RCosU = MajorRadius * cosu;
    const double RSinU = MajorRadius * sinu;
    const double xm    = x - RCosU;
    const double ym    = y - RSinU;
    const double xp    = x + RCosU;
    const double yp    = y + RSinU;
    const double D1    = xm * xm + ym * ym + z2 - MinR2;
    const double D2    = xp * xp + yp * yp + z2 - MinR2;
    const double AD1   = std::abs(D1);
    const double AD2   = std::abs(D2);
    if (AD2 < AD1)
      U += M_PI;
  }
  normalizeAngle(U);
  const double cosu = cos(U);
  const double sinu = sin(U);
  const gp_Dir dx(cosu, sinu, 0.);
  const gp_XYZ dPV(x - MajorRadius * cosu, y - MajorRadius * sinu, z);
  const double aMag = dPV.Modulus();
  if (aMag <= gp::Resolution())
  {
    V = 0.;
  }
  else
  {
    gp_Dir dP(dPV);
    V = dx.AngleWithRef(dP, dx ^ gp::DZ());
  }
  normalizeAngle(V);
}

gp_Lin ElSLib::PlaneUIso(const gp_Ax3& Pos, const double U)
{
  gp_Lin L(Pos.Location(), Pos.YDirection());
  gp_Vec Ve(Pos.XDirection());
  Ve *= U;
  L.Translate(Ve);
  return L;
}

gp_Lin ElSLib::CylinderUIso(const gp_Ax3& Pos, const double Radius, const double U)
{
  gp_Pnt P;
  gp_Vec DU, DV;
  CylinderD1(U, 0., Pos, Radius, P, DU, DV);
  gp_Lin L(P, DV);
  return L;
}

gp_Lin ElSLib::ConeUIso(const gp_Ax3& Pos, const double Radius, const double SAngle, const double U)
{
  gp_Pnt P;
  gp_Vec DU, DV;
  ConeD1(U, 0, Pos, Radius, SAngle, P, DU, DV);
  gp_Lin L(P, DV);
  return L;
}

gp_Circ ElSLib::SphereUIso(const gp_Ax3& Pos, const double Radius, const double U)
{
  gp_Vec  dx = Pos.XDirection();
  gp_Vec  dy = Pos.YDirection();
  gp_Dir  dz = Pos.Direction();
  gp_Dir  cx = cos(U) * dx + sin(U) * dy;
  gp_Ax2  axes(Pos.Location(), cx.Crossed(dz), cx);
  gp_Circ Circ(axes, Radius);
  return Circ;
}

gp_Circ ElSLib::TorusUIso(const gp_Ax3& Pos,
                          const double  MajorRadius,
                          const double  MinorRadius,
                          const double  U)
{
  gp_Vec dx = Pos.XDirection();
  gp_Vec dy = Pos.YDirection();
  gp_Dir dz = Pos.Direction();
  gp_Dir cx = cos(U) * dx + sin(U) * dy;
  gp_Ax2 axes(Pos.Location(), cx.Crossed(dz), cx);
  gp_Vec Ve = cx;
  Ve *= MajorRadius;
  axes.Translate(Ve);
  gp_Circ Circ(axes, MinorRadius);
  return Circ;
}

gp_Lin ElSLib::PlaneVIso(const gp_Ax3& Pos, const double V)
{
  gp_Lin L(Pos.Location(), Pos.XDirection());
  gp_Vec Ve(Pos.YDirection());
  Ve *= V;
  L.Translate(Ve);
  return L;
}

gp_Circ ElSLib::CylinderVIso(const gp_Ax3& Pos, const double Radius, const double V)
{
  gp_Ax2 axes = Pos.Ax2();
  gp_Vec Ve(Pos.Direction());
  Ve.Multiply(V);
  axes.Translate(Ve);
  gp_Circ C(axes, Radius);
  return C;
}

gp_Circ ElSLib::ConeVIso(const gp_Ax3& Pos,
                         const double  Radius,
                         const double  SAngle,
                         const double  V)
{
  gp_Ax3 axes(Pos);
  gp_Vec Ve(Pos.Direction());
  Ve.Multiply(V * cos(SAngle));
  axes.Translate(Ve);
  double R = Radius + V * sin(SAngle);
  if (R < 0)
  {
    axes.XReverse();
    axes.YReverse();
    R = -R;
  }
  gp_Circ C(axes.Ax2(), R);
  return C;
}

gp_Circ ElSLib::SphereVIso(const gp_Ax3& Pos, const double Radius, const double V)
{
  gp_Ax2 axes = Pos.Ax2();
  gp_Vec Ve(Pos.Direction());
  Ve.Multiply(Radius * sin(V));
  axes.Translate(Ve);
  double radius = Radius * cos(V);

  if (radius < 0.)
  {
    axes.SetDirection(-axes.Direction());
    radius = -radius;
  }
  gp_Circ Circ(axes, radius);
  return Circ;
}

gp_Circ ElSLib::TorusVIso(const gp_Ax3& Pos,
                          const double  MajorRadius,
                          const double  MinorRadius,
                          const double  V)
{
  gp_Ax3 axes = Pos.Ax2();
  gp_Vec Ve(Pos.Direction());
  Ve.Multiply(MinorRadius * sin(V));
  axes.Translate(Ve);
  double R = MajorRadius + MinorRadius * cos(V);
  if (R < 0)
  {
    axes.XReverse();
    axes.YReverse();
    R = -R;
  }
  gp_Circ Circ(axes.Ax2(), R);
  return Circ;
}
