#include <Geom2d_Vector.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom2d_Vector, Geom2d_Geometry)

typedef Geom2d_Vector Vector;
typedef gp_Ax2d       Ax2d;
typedef gp_Pnt2d      Pnt2d;

double Geom2d_Vector::Angle(const occ::handle<Geom2d_Vector>& Other) const
{

  return gpVec2d.Angle(Other->Vec2d());
}

void Geom2d_Vector::Reverse()
{
  gpVec2d.Reverse();
}

gp_Vec2d Geom2d_Vector::Vec2d() const
{
  return gpVec2d;
}

double Geom2d_Vector::X() const
{
  return gpVec2d.X();
}

double Geom2d_Vector::Y() const
{
  return gpVec2d.Y();
}

occ::handle<Geom2d_Vector> Geom2d_Vector::Reversed() const
{

  occ::handle<Geom2d_Vector> V = occ::down_cast<Geom2d_Vector>(Copy());
  V->Reverse();
  return V;
}

void Geom2d_Vector::Coord(double& X, double& Y) const
{

  gpVec2d.Coord(X, Y);
}

double Geom2d_Vector::Dot(const occ::handle<Geom2d_Vector>& Other) const
{

  return gpVec2d.Dot(Other->Vec2d());
}
