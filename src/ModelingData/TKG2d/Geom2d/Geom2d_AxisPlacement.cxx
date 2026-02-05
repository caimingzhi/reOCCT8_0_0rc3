#include <Geom2d_AxisPlacement.hpp>
#include <Geom2d_Geometry.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom2d_AxisPlacement, Geom2d_Geometry)

typedef Geom2d_AxisPlacement AxisPlacement;
typedef gp_Dir2d             Dir2d;
typedef gp_Pnt2d             Pnt2d;
typedef gp_Trsf2d            Trsf2d;
typedef gp_Vec2d             Vec2d;

occ::handle<Geom2d_Geometry> Geom2d_AxisPlacement::Copy() const
{

  occ::handle<Geom2d_AxisPlacement> A;
  A = new AxisPlacement(axis);
  return A;
}

Geom2d_AxisPlacement::Geom2d_AxisPlacement(const gp_Ax2d& A)
{
  axis = A;
}

Geom2d_AxisPlacement::Geom2d_AxisPlacement(const Pnt2d& P, const Dir2d& V)
{

  axis = gp_Ax2d(P, V);
}

gp_Ax2d Geom2d_AxisPlacement::Ax2d() const
{
  return axis;
}

Dir2d Geom2d_AxisPlacement::Direction() const
{
  return axis.Direction();
}

Pnt2d Geom2d_AxisPlacement::Location() const
{
  return axis.Location();
}

void Geom2d_AxisPlacement::Reverse()
{
  axis.Reverse();
}

occ::handle<Geom2d_AxisPlacement> Geom2d_AxisPlacement::Reversed() const
{

  gp_Ax2d A = axis;
  A.Reverse();
  occ::handle<Geom2d_AxisPlacement> Temp = new AxisPlacement(A);
  return Temp;
}

void Geom2d_AxisPlacement::Transform(const Trsf2d& T)
{
  axis.Transform(T);
}

void Geom2d_AxisPlacement::SetAxis(const gp_Ax2d& A)
{
  axis = A;
}

void Geom2d_AxisPlacement::SetLocation(const Pnt2d& P)
{
  axis.SetLocation(P);
}

void Geom2d_AxisPlacement::SetDirection(const Dir2d& V)
{

  axis.SetDirection(V);
}

double Geom2d_AxisPlacement::Angle(const occ::handle<Geom2d_AxisPlacement>& Other) const
{

  return axis.Angle(Other->Ax2d());
}
