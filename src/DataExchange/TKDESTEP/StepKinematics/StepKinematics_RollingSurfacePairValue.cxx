

#include <StepKinematics_RollingSurfacePairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_RollingSurfacePairValue, StepKinematics_PairValue)

StepKinematics_RollingSurfacePairValue::StepKinematics_RollingSurfacePairValue() = default;

void StepKinematics_RollingSurfacePairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface,
  const double                                     theActualRotation)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualPointOnSurface = theActualPointOnSurface;

  myActualRotation = theActualRotation;
}

occ::handle<StepGeom_PointOnSurface> StepKinematics_RollingSurfacePairValue::ActualPointOnSurface()
  const
{
  return myActualPointOnSurface;
}

void StepKinematics_RollingSurfacePairValue::SetActualPointOnSurface(
  const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface)
{
  myActualPointOnSurface = theActualPointOnSurface;
}

double StepKinematics_RollingSurfacePairValue::ActualRotation() const
{
  return myActualRotation;
}

void StepKinematics_RollingSurfacePairValue::SetActualRotation(const double theActualRotation)
{
  myActualRotation = theActualRotation;
}
