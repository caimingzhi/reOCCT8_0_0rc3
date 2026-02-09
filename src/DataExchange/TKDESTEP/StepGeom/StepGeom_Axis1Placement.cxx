

#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Axis1Placement, StepGeom_Placement)

StepGeom_Axis1Placement::StepGeom_Axis1Placement() = default;

void StepGeom_Axis1Placement::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                   const occ::handle<StepGeom_CartesianPoint>&  aLocation,
                                   const bool                                   hasAaxis,
                                   const occ::handle<StepGeom_Direction>&       aAxis)
{

  hasAxis = hasAaxis;
  axis    = aAxis;

  StepGeom_Placement::Init(aName, aLocation);
}

void StepGeom_Axis1Placement::SetAxis(const occ::handle<StepGeom_Direction>& aAxis)
{
  axis    = aAxis;
  hasAxis = true;
}

void StepGeom_Axis1Placement::UnSetAxis()
{
  hasAxis = false;
  axis.Nullify();
}

occ::handle<StepGeom_Direction> StepGeom_Axis1Placement::Axis() const
{
  return axis;
}

bool StepGeom_Axis1Placement::HasAxis() const
{
  return hasAxis;
}
