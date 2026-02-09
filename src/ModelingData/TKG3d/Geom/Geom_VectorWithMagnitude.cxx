#include <Geom_Geometry.hpp>
#include <Geom_Vector.hpp>
#include <Geom_VectorWithMagnitude.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_VectorWithMagnitude, Geom_Vector)

typedef Geom_VectorWithMagnitude VectorWithMagnitude;
typedef Geom_Vector              Vector;
typedef gp_Ax1                   Ax1;
typedef gp_Ax2                   Ax2;
typedef gp_Pnt                   Pnt;
typedef gp_Trsf                  Trsf;

Geom_VectorWithMagnitude::Geom_VectorWithMagnitude(const gp_Vec& V)
{
  gpVec = V;
}

Geom_VectorWithMagnitude::Geom_VectorWithMagnitude(const double X, const double Y, const double Z)
{
  gpVec = gp_Vec(X, Y, Z);
}

Geom_VectorWithMagnitude::Geom_VectorWithMagnitude(const Pnt& P1, const Pnt& P2)
{
  gpVec = gp_Vec(P1, P2);
}

occ::handle<Geom_Geometry> Geom_VectorWithMagnitude::Copy() const
{

  occ::handle<Geom_VectorWithMagnitude> V;
  V = new VectorWithMagnitude(gpVec);
  return V;
}

void Geom_VectorWithMagnitude::SetCoord(const double X, const double Y, const double Z)
{
  gpVec = gp_Vec(X, Y, Z);
}

void Geom_VectorWithMagnitude::SetVec(const gp_Vec& V)
{
  gpVec = V;
}

void Geom_VectorWithMagnitude::SetX(const double X)
{
  gpVec.SetX(X);
}

void Geom_VectorWithMagnitude::SetY(const double Y)
{
  gpVec.SetY(Y);
}

void Geom_VectorWithMagnitude::SetZ(const double Z)
{
  gpVec.SetZ(Z);
}

double Geom_VectorWithMagnitude::Magnitude() const
{
  return gpVec.Magnitude();
}

double Geom_VectorWithMagnitude::SquareMagnitude() const
{

  return gpVec.SquareMagnitude();
}

void Geom_VectorWithMagnitude::Add(const occ::handle<Geom_Vector>& Other)
{

  gpVec.Add(Other->Vec());
}

occ::handle<Geom_VectorWithMagnitude> Geom_VectorWithMagnitude::Added(
  const occ::handle<Geom_Vector>& Other) const
{

  gp_Vec V1 = gpVec;
  V1.Add(Other->Vec());
  return new VectorWithMagnitude(V1);
}

void Geom_VectorWithMagnitude::Cross(const occ::handle<Geom_Vector>& Other)
{

  gpVec.Cross(Other->Vec());
}

occ::handle<Geom_Vector> Geom_VectorWithMagnitude::Crossed(
  const occ::handle<Geom_Vector>& Other) const
{

  gp_Vec V(gpVec);
  V.Cross(Other->Vec());
  return new VectorWithMagnitude(V);
}

void Geom_VectorWithMagnitude::CrossCross(const occ::handle<Geom_Vector>& V1,
                                          const occ::handle<Geom_Vector>& V2)
{

  gpVec.CrossCross(V1->Vec(), V2->Vec());
}

occ::handle<Geom_Vector> Geom_VectorWithMagnitude::CrossCrossed(
  const occ::handle<Geom_Vector>& V1,
  const occ::handle<Geom_Vector>& V2) const
{

  gp_Vec V(gpVec);
  V.CrossCross(V1->Vec(), V2->Vec());
  return new VectorWithMagnitude(V);
}

void Geom_VectorWithMagnitude::Divide(const double Scalar)
{

  gpVec.Divide(Scalar);
}

occ::handle<Geom_VectorWithMagnitude> Geom_VectorWithMagnitude::Divided(const double Scalar) const
{

  gp_Vec V(gpVec);
  V.Divide(Scalar);
  return new VectorWithMagnitude(V);
}

occ::handle<Geom_VectorWithMagnitude> Geom_VectorWithMagnitude::Multiplied(
  const double Scalar) const
{

  gp_Vec V(gpVec);
  V.Multiply(Scalar);
  return new VectorWithMagnitude(V);
}

void Geom_VectorWithMagnitude::Multiply(const double Scalar)
{

  gpVec.Multiply(Scalar);
}

void Geom_VectorWithMagnitude::Normalize()
{
  gpVec.Normalize();
}

occ::handle<Geom_VectorWithMagnitude> Geom_VectorWithMagnitude::Normalized() const
{

  gp_Vec V(gpVec);
  V.Normalize();
  return new VectorWithMagnitude(V);
}

void Geom_VectorWithMagnitude::Subtract(const occ::handle<Geom_Vector>& Other)
{

  gpVec.Subtract(Other->Vec());
}

occ::handle<Geom_VectorWithMagnitude> Geom_VectorWithMagnitude::Subtracted(
  const occ::handle<Geom_Vector>& Other) const
{

  gp_Vec V(gpVec);
  V.Subtract(Other->Vec());
  return new VectorWithMagnitude(V);
}

void Geom_VectorWithMagnitude::Transform(const Trsf& T)
{

  gpVec.Transform(T);
}
