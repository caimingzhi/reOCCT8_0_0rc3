

#include <StepKinematics_PointOnSurfacePairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PointOnSurfacePairValue, StepKinematics_PairValue)

StepKinematics_PointOnSurfacePairValue::StepKinematics_PointOnSurfacePairValue() = default;

void StepKinematics_PointOnSurfacePairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface,
  const StepKinematics_SpatialRotation&            theInputOrientation)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualPointOnSurface = theActualPointOnSurface;

  myInputOrientation = theInputOrientation;
}

occ::handle<StepGeom_PointOnSurface> StepKinematics_PointOnSurfacePairValue::ActualPointOnSurface()
  const
{
  return myActualPointOnSurface;
}

void StepKinematics_PointOnSurfacePairValue::SetActualPointOnSurface(
  const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface)
{
  myActualPointOnSurface = theActualPointOnSurface;
}

StepKinematics_SpatialRotation StepKinematics_PointOnSurfacePairValue::InputOrientation() const
{
  return myInputOrientation;
}

void StepKinematics_PointOnSurfacePairValue::SetInputOrientation(
  const StepKinematics_SpatialRotation& theInputOrientation)
{
  myInputOrientation = theInputOrientation;
}
