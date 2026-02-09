

#include <StepKinematics_SphericalPairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_SphericalPairValue, StepKinematics_PairValue)

StepKinematics_SphericalPairValue::StepKinematics_SphericalPairValue() = default;

void StepKinematics_SphericalPairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const StepKinematics_SpatialRotation&            theInputOrientation)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myInputOrientation = theInputOrientation;
}

StepKinematics_SpatialRotation StepKinematics_SphericalPairValue::InputOrientation() const
{
  return myInputOrientation;
}

void StepKinematics_SphericalPairValue::SetInputOrientation(
  const StepKinematics_SpatialRotation& theInputOrientation)
{
  myInputOrientation = theInputOrientation;
}
