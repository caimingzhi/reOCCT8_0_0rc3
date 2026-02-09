#include <Geom_Axis1Placement.hpp>
#include <Geom_Geometry.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Axis1Placement, Geom_AxisPlacement)

typedef Geom_Axis1Placement Axis1Placement;
typedef gp_Ax2              Ax2;
typedef gp_Dir              Dir;
typedef gp_Pnt              Pnt;
typedef gp_Trsf             Trsf;
typedef gp_Vec              Vec;

occ::handle<Geom_Geometry> Geom_Axis1Placement::Copy() const
{

  occ::handle<Geom_Axis1Placement> A1;
  A1 = new Axis1Placement(axis);
  return A1;
}

Geom_Axis1Placement::Geom_Axis1Placement(const gp_Ax1& A1)
{
  axis = A1;
}

Geom_Axis1Placement::Geom_Axis1Placement(const Pnt& P, const Dir& V)
{

  axis = gp_Ax1(P, V);
}

void Geom_Axis1Placement::SetDirection(const Dir& V)
{
  axis.SetDirection(V);
}

const gp_Ax1& Geom_Axis1Placement::Ax1() const
{
  return Axis();
}

void Geom_Axis1Placement::Reverse()
{
  axis.Reverse();
}

void Geom_Axis1Placement::Transform(const Trsf& T)
{
  axis.Transform(T);
}

occ::handle<Geom_Axis1Placement> Geom_Axis1Placement::Reversed() const
{

  gp_Ax1 A1 = axis;
  A1.Reverse();
  occ::handle<Axis1Placement> Temp = new Axis1Placement(A1);
  return Temp;
}
