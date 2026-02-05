#include <Blend_Point.hpp>
#include <Blend_SurfRstFunction.hpp>
#include <gp_Pnt.hpp>
#include <Standard_NotImplemented.hpp>

const gp_Pnt& Blend_SurfRstFunction::Pnt1() const
{
  return PointOnS();
}

const gp_Pnt& Blend_SurfRstFunction::Pnt2() const
{
  return PointOnRst();
}

double Blend_SurfRstFunction::GetMinimalDistance() const
{
  throw Standard_NotImplemented("Blend_SurfRstFunction::GetMinimalDistance");
}
