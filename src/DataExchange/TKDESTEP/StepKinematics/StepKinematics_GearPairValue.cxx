

#include <StepKinematics_GearPairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_GearPairValue, StepKinematics_PairValue)

StepKinematics_GearPairValue::StepKinematics_GearPairValue() = default;

void StepKinematics_GearPairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const double                                     theActualRotation1)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualRotation1 = theActualRotation1;
}

double StepKinematics_GearPairValue::ActualRotation1() const
{
  return myActualRotation1;
}

void StepKinematics_GearPairValue::SetActualRotation1(const double theActualRotation1)
{
  myActualRotation1 = theActualRotation1;
}
