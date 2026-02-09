

#include <StepKinematics_RackAndPinionPairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_RackAndPinionPairValue, StepKinematics_PairValue)

StepKinematics_RackAndPinionPairValue::StepKinematics_RackAndPinionPairValue() = default;

void StepKinematics_RackAndPinionPairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const double                                     theActualDisplacement)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualDisplacement = theActualDisplacement;
}

double StepKinematics_RackAndPinionPairValue::ActualDisplacement() const
{
  return myActualDisplacement;
}

void StepKinematics_RackAndPinionPairValue::SetActualDisplacement(
  const double theActualDisplacement)
{
  myActualDisplacement = theActualDisplacement;
}
