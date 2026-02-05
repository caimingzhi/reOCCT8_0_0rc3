#include <Blend_Point.hpp>
#include <Blend_RstRstFunction.hpp>
#include <gp_Pnt.hpp>
#include <Standard_NotImplemented.hpp>

const gp_Pnt& Blend_RstRstFunction::Pnt1() const
{
  return PointOnRst1();
}

const gp_Pnt& Blend_RstRstFunction::Pnt2() const
{
  return PointOnRst2();
}

double Blend_RstRstFunction::GetMinimalDistance() const
{
  throw Standard_NotImplemented("Blend_RstRstFunction::GetMinimalDistance");
}
