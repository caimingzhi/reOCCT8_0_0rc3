

#include <StepKinematics_ScrewPairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_ScrewPairValue, StepKinematics_PairValue)

StepKinematics_ScrewPairValue::StepKinematics_ScrewPairValue() = default;

void StepKinematics_ScrewPairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const double                                     theActualRotation)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualRotation = theActualRotation;
}

double StepKinematics_ScrewPairValue::ActualRotation() const
{
  return myActualRotation;
}

void StepKinematics_ScrewPairValue::SetActualRotation(const double theActualRotation)
{
  myActualRotation = theActualRotation;
}
