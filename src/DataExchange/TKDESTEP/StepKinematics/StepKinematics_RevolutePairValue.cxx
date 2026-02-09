

#include <StepKinematics_RevolutePairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_RevolutePairValue, StepKinematics_PairValue)

StepKinematics_RevolutePairValue::StepKinematics_RevolutePairValue() = default;

void StepKinematics_RevolutePairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const double                                     theActualRotation)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualRotation = theActualRotation;
}

double StepKinematics_RevolutePairValue::ActualRotation() const
{
  return myActualRotation;
}

void StepKinematics_RevolutePairValue::SetActualRotation(const double theActualRotation)
{
  myActualRotation = theActualRotation;
}
