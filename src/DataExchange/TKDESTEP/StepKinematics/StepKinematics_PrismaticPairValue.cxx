// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_PrismaticPairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PrismaticPairValue, StepKinematics_PairValue)

//=================================================================================================

StepKinematics_PrismaticPairValue::StepKinematics_PrismaticPairValue() = default;

//=================================================================================================

void StepKinematics_PrismaticPairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const double                                     theActualTranslation)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualTranslation = theActualTranslation;
}

//=================================================================================================

double StepKinematics_PrismaticPairValue::ActualTranslation() const
{
  return myActualTranslation;
}

//=================================================================================================

void StepKinematics_PrismaticPairValue::SetActualTranslation(const double theActualTranslation)
{
  myActualTranslation = theActualTranslation;
}
