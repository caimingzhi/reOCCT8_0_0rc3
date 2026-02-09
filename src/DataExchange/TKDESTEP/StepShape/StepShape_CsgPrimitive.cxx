

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepShape_Block.hpp>
#include <StepShape_CsgPrimitive.hpp>
#include <StepShape_RightAngularWedge.hpp>
#include <StepShape_RightCircularCone.hpp>
#include <StepShape_RightCircularCylinder.hpp>
#include <StepShape_Sphere.hpp>
#include <StepShape_Torus.hpp>

StepShape_CsgPrimitive::StepShape_CsgPrimitive() = default;

int StepShape_CsgPrimitive::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepShape_Sphere)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_Block)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepShape_RightAngularWedge)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepShape_Torus)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepShape_RightCircularCone)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepShape_RightCircularCylinder)))
    return 6;
  return 0;
}

occ::handle<StepShape_Sphere> StepShape_CsgPrimitive::Sphere() const
{
  return GetCasted(StepShape_Sphere, Value());
}

occ::handle<StepShape_Block> StepShape_CsgPrimitive::Block() const
{
  return GetCasted(StepShape_Block, Value());
}

occ::handle<StepShape_RightAngularWedge> StepShape_CsgPrimitive::RightAngularWedge() const
{
  return GetCasted(StepShape_RightAngularWedge, Value());
}

occ::handle<StepShape_Torus> StepShape_CsgPrimitive::Torus() const
{
  return GetCasted(StepShape_Torus, Value());
}

occ::handle<StepShape_RightCircularCone> StepShape_CsgPrimitive::RightCircularCone() const
{
  return GetCasted(StepShape_RightCircularCone, Value());
}

occ::handle<StepShape_RightCircularCylinder> StepShape_CsgPrimitive::RightCircularCylinder() const
{
  return GetCasted(StepShape_RightCircularCylinder, Value());
}
