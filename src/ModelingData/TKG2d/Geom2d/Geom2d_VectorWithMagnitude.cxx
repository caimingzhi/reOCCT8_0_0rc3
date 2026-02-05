#include <Geom2d_Geometry.hpp>
#include <Geom2d_Vector.hpp>
#include <Geom2d_VectorWithMagnitude.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom2d_VectorWithMagnitude, Geom2d_Vector)

typedef Geom2d_Vector              Vector;
typedef Geom2d_VectorWithMagnitude VectorWithMagnitude;
typedef gp_Ax2d                    Ax2d;
typedef gp_Pnt2d                   Pnt2d;
typedef gp_Trsf2d                  Trsf2d;

Geom2d_VectorWithMagnitude::Geom2d_VectorWithMagnitude(const gp_Vec2d& V)
{
  gpVec2d = V;
}

Geom2d_VectorWithMagnitude::Geom2d_VectorWithMagnitude(const double X, const double Y)
{
  gpVec2d = gp_Vec2d(X, Y);
}

Geom2d_VectorWithMagnitude::Geom2d_VectorWithMagnitude(const Pnt2d& P1, const Pnt2d& P2)
{
  gpVec2d = gp_Vec2d(P1, P2);
}

occ::handle<Geom2d_Geometry> Geom2d_VectorWithMagnitude::Copy() const
{

  occ::handle<Geom2d_VectorWithMagnitude> V;
  V = new VectorWithMagnitude(gpVec2d);
  return V;
}

void Geom2d_VectorWithMagnitude::SetCoord(const double X, const double Y)
{

  gpVec2d = gp_Vec2d(X, Y);
}

void Geom2d_VectorWithMagnitude::SetVec2d(const gp_Vec2d& V)
{
  gpVec2d = V;
}

void Geom2d_VectorWithMagnitude::SetX(const double X)
{
  gpVec2d.SetX(X);
}

void Geom2d_VectorWithMagnitude::SetY(const double Y)
{
  gpVec2d.SetY(Y);
}

double Geom2d_VectorWithMagnitude::Magnitude() const
{

  return gpVec2d.Magnitude();
}

double Geom2d_VectorWithMagnitude::SquareMagnitude() const
{

  return gpVec2d.SquareMagnitude();
}

void Geom2d_VectorWithMagnitude::Add(const occ::handle<Geom2d_Vector>& Other)
{

  gpVec2d.Add(Other->Vec2d());
}

occ::handle<Geom2d_VectorWithMagnitude> Geom2d_VectorWithMagnitude::Added(

  const occ::handle<Geom2d_Vector>& Other) const
{

  gp_Vec2d Temp = Other->Vec2d();
  Temp.Add(gpVec2d);
  return new VectorWithMagnitude(Temp);
}

double Geom2d_VectorWithMagnitude::Crossed(const occ::handle<Geom2d_Vector>& Other) const
{

  return gpVec2d.Crossed(Other->Vec2d());
}

void Geom2d_VectorWithMagnitude::Divide(const double Scalar)
{

  gpVec2d.Divide(Scalar);
}

occ::handle<Geom2d_VectorWithMagnitude> Geom2d_VectorWithMagnitude::Divided(
  const double Scalar) const
{

  gp_Vec2d V(gpVec2d);
  V.Divide(Scalar);
  return new VectorWithMagnitude(V);
}

occ::handle<Geom2d_VectorWithMagnitude> Geom2d_VectorWithMagnitude::Multiplied(
  const double Scalar) const
{

  gp_Vec2d V(gpVec2d);
  V.Multiply(Scalar);
  return new VectorWithMagnitude(V);
}

void Geom2d_VectorWithMagnitude::Multiply(const double Scalar)
{

  gpVec2d.Multiply(Scalar);
}

void Geom2d_VectorWithMagnitude::Normalize()
{
  gpVec2d.Normalize();
}

occ::handle<Geom2d_VectorWithMagnitude> Geom2d_VectorWithMagnitude::Normalized() const
{

  gp_Vec2d V = gpVec2d.Normalized();
  return new VectorWithMagnitude(V);
}

void Geom2d_VectorWithMagnitude::Subtract(const occ::handle<Geom2d_Vector>& Other)
{

  gpVec2d.Subtract(Other->Vec2d());
}

occ::handle<Geom2d_VectorWithMagnitude> Geom2d_VectorWithMagnitude::Subtracted(
  const occ::handle<Geom2d_Vector>& Other) const
{

  gp_Vec2d V = gpVec2d;
  V.Subtract(Other->Vec2d());
  return new VectorWithMagnitude(V);
}

void Geom2d_VectorWithMagnitude::Transform(const Trsf2d& T)
{

  gpVec2d.Transform(T);
}
