

#include <StepGeom_Axis2Placement2d.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Axis2Placement2d, StepGeom_Placement)

StepGeom_Axis2Placement2d::StepGeom_Axis2Placement2d() = default;

void StepGeom_Axis2Placement2d::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                     const occ::handle<StepGeom_CartesianPoint>&  aLocation,
                                     const bool                                   hasArefDirection,
                                     const occ::handle<StepGeom_Direction>&       aRefDirection)
{

  hasRefDirection = hasArefDirection;
  refDirection    = aRefDirection;

  StepGeom_Placement::Init(aName, aLocation);
}

void StepGeom_Axis2Placement2d::SetRefDirection(
  const occ::handle<StepGeom_Direction>& aRefDirection)
{
  refDirection    = aRefDirection;
  hasRefDirection = true;
}

void StepGeom_Axis2Placement2d::UnSetRefDirection()
{
  hasRefDirection = false;
  refDirection.Nullify();
}

occ::handle<StepGeom_Direction> StepGeom_Axis2Placement2d::RefDirection() const
{
  return refDirection;
}

bool StepGeom_Axis2Placement2d::HasRefDirection() const
{
  return hasRefDirection;
}
