// Created on : Sat May 02 12:41:16 2020

#include <StepKinematics_UniversalPairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_UniversalPairValue, StepKinematics_PairValue)

//=================================================================================================

StepKinematics_UniversalPairValue::StepKinematics_UniversalPairValue() = default;

//=================================================================================================

void StepKinematics_UniversalPairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const double                                     theFirstRotationAngle,
  const double                                     theSecondRotationAngle)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myFirstRotationAngle = theFirstRotationAngle;

  mySecondRotationAngle = theSecondRotationAngle;
}

//=================================================================================================

double StepKinematics_UniversalPairValue::FirstRotationAngle() const
{
  return myFirstRotationAngle;
}

//=================================================================================================

void StepKinematics_UniversalPairValue::SetFirstRotationAngle(const double theFirstRotationAngle)
{
  myFirstRotationAngle = theFirstRotationAngle;
}

//=================================================================================================

double StepKinematics_UniversalPairValue::SecondRotationAngle() const
{
  return mySecondRotationAngle;
}

//=================================================================================================

void StepKinematics_UniversalPairValue::SetSecondRotationAngle(const double theSecondRotationAngle)
{
  mySecondRotationAngle = theSecondRotationAngle;
}
