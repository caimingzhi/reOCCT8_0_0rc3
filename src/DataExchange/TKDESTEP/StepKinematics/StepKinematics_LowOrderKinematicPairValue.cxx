

#include <StepKinematics_LowOrderKinematicPairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_LowOrderKinematicPairValue, StepKinematics_PairValue)

StepKinematics_LowOrderKinematicPairValue::StepKinematics_LowOrderKinematicPairValue() = default;

void StepKinematics_LowOrderKinematicPairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const double                                     theActualTranslationX,
  const double                                     theActualTranslationY,
  const double                                     theActualTranslationZ,
  const double                                     theActualRotationX,
  const double                                     theActualRotationY,
  const double                                     theActualRotationZ)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualTranslationX = theActualTranslationX;

  myActualTranslationY = theActualTranslationY;

  myActualTranslationZ = theActualTranslationZ;

  myActualRotationX = theActualRotationX;

  myActualRotationY = theActualRotationY;

  myActualRotationZ = theActualRotationZ;
}

double StepKinematics_LowOrderKinematicPairValue::ActualTranslationX() const
{
  return myActualTranslationX;
}

void StepKinematics_LowOrderKinematicPairValue::SetActualTranslationX(
  const double theActualTranslationX)
{
  myActualTranslationX = theActualTranslationX;
}

double StepKinematics_LowOrderKinematicPairValue::ActualTranslationY() const
{
  return myActualTranslationY;
}

void StepKinematics_LowOrderKinematicPairValue::SetActualTranslationY(
  const double theActualTranslationY)
{
  myActualTranslationY = theActualTranslationY;
}

double StepKinematics_LowOrderKinematicPairValue::ActualTranslationZ() const
{
  return myActualTranslationZ;
}

void StepKinematics_LowOrderKinematicPairValue::SetActualTranslationZ(
  const double theActualTranslationZ)
{
  myActualTranslationZ = theActualTranslationZ;
}

double StepKinematics_LowOrderKinematicPairValue::ActualRotationX() const
{
  return myActualRotationX;
}

void StepKinematics_LowOrderKinematicPairValue::SetActualRotationX(const double theActualRotationX)
{
  myActualRotationX = theActualRotationX;
}

double StepKinematics_LowOrderKinematicPairValue::ActualRotationY() const
{
  return myActualRotationY;
}

void StepKinematics_LowOrderKinematicPairValue::SetActualRotationY(const double theActualRotationY)
{
  myActualRotationY = theActualRotationY;
}

double StepKinematics_LowOrderKinematicPairValue::ActualRotationZ() const
{
  return myActualRotationZ;
}

void StepKinematics_LowOrderKinematicPairValue::SetActualRotationZ(const double theActualRotationZ)
{
  myActualRotationZ = theActualRotationZ;
}
