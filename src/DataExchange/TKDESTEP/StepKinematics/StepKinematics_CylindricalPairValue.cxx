

#include <StepKinematics_CylindricalPairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_CylindricalPairValue, StepKinematics_PairValue)

StepKinematics_CylindricalPairValue::StepKinematics_CylindricalPairValue() = default;

void StepKinematics_CylindricalPairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const double                                     theActualTranslation,
  const double                                     theActualRotation)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualTranslation = theActualTranslation;

  myActualRotation = theActualRotation;
}

double StepKinematics_CylindricalPairValue::ActualTranslation() const
{
  return myActualTranslation;
}

void StepKinematics_CylindricalPairValue::SetActualTranslation(const double theActualTranslation)
{
  myActualTranslation = theActualTranslation;
}

double StepKinematics_CylindricalPairValue::ActualRotation() const
{
  return myActualRotation;
}

void StepKinematics_CylindricalPairValue::SetActualRotation(const double theActualRotation)
{
  myActualRotation = theActualRotation;
}
