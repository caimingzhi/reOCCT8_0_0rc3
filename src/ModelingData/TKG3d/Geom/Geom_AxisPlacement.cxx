#include <Geom_AxisPlacement.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_AxisPlacement, Geom_Geometry)

typedef gp_Ax1 Ax1;
typedef gp_Dir Dir;
typedef gp_Pnt Pnt;
typedef gp_Vec Vec;

const gp_Ax1& Geom_AxisPlacement::Axis() const
{
  return axis;
}

Dir Geom_AxisPlacement::Direction() const
{
  return axis.Direction();
}

Pnt Geom_AxisPlacement::Location() const
{
  return axis.Location();
}

void Geom_AxisPlacement::SetAxis(const Ax1& A1)
{
  axis = A1;
}

void Geom_AxisPlacement::SetLocation(const Pnt& P)
{
  axis.SetLocation(P);
}

double Geom_AxisPlacement::Angle(const occ::handle<Geom_AxisPlacement>& Other) const
{
  return axis.Angle(Other->Axis());
}
