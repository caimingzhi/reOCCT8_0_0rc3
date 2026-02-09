

#include <StepKinematics_PlanarPairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PlanarPairValue, StepKinematics_PairValue)

StepKinematics_PlanarPairValue::StepKinematics_PlanarPairValue() = default;

void StepKinematics_PlanarPairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const double                                     theActualRotation,
  const double                                     theActualTranslationX,
  const double                                     theActualTranslationY)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualRotation = theActualRotation;

  myActualTranslationX = theActualTranslationX;

  myActualTranslationY = theActualTranslationY;
}

double StepKinematics_PlanarPairValue::ActualRotation() const
{
  return myActualRotation;
}

void StepKinematics_PlanarPairValue::SetActualRotation(const double theActualRotation)
{
  myActualRotation = theActualRotation;
}

double StepKinematics_PlanarPairValue::ActualTranslationX() const
{
  return myActualTranslationX;
}

void StepKinematics_PlanarPairValue::SetActualTranslationX(const double theActualTranslationX)
{
  myActualTranslationX = theActualTranslationX;
}

double StepKinematics_PlanarPairValue::ActualTranslationY() const
{
  return myActualTranslationY;
}

void StepKinematics_PlanarPairValue::SetActualTranslationY(const double theActualTranslationY)
{
  myActualTranslationY = theActualTranslationY;
}
