// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_CylindricalPairWithRange.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_CylindricalPairWithRange, StepKinematics_CylindricalPair)

//=================================================================================================

StepKinematics_CylindricalPairWithRange::StepKinematics_CylindricalPairWithRange()
{
  defLowerLimitActualTranslation = false;
  defUpperLimitActualTranslation = false;
  defLowerLimitActualRotation    = false;
  defUpperLimitActualRotation    = false;
}

//=================================================================================================

void StepKinematics_CylindricalPairWithRange::Init(
  const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
  const bool                                        hasItemDefinedTransformation_Description,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
  const bool                                        theLowOrderKinematicPair_TX,
  const bool                                        theLowOrderKinematicPair_TY,
  const bool                                        theLowOrderKinematicPair_TZ,
  const bool                                        theLowOrderKinematicPair_RX,
  const bool                                        theLowOrderKinematicPair_RY,
  const bool                                        theLowOrderKinematicPair_RZ,
  const bool                                        hasLowerLimitActualTranslation,
  const double                                      theLowerLimitActualTranslation,
  const bool                                        hasUpperLimitActualTranslation,
  const double                                      theUpperLimitActualTranslation,
  const bool                                        hasLowerLimitActualRotation,
  const double                                      theLowerLimitActualRotation,
  const bool                                        hasUpperLimitActualRotation,
  const double                                      theUpperLimitActualRotation)
{
  StepKinematics_CylindricalPair::Init(theRepresentationItem_Name,
                                       theItemDefinedTransformation_Name,
                                       hasItemDefinedTransformation_Description,
                                       theItemDefinedTransformation_Description,
                                       theItemDefinedTransformation_TransformItem1,
                                       theItemDefinedTransformation_TransformItem2,
                                       theKinematicPair_Joint,
                                       theLowOrderKinematicPair_TX,
                                       theLowOrderKinematicPair_TY,
                                       theLowOrderKinematicPair_TZ,
                                       theLowOrderKinematicPair_RX,
                                       theLowOrderKinematicPair_RY,
                                       theLowOrderKinematicPair_RZ);

  defLowerLimitActualTranslation = hasLowerLimitActualTranslation;
  if (defLowerLimitActualTranslation)
  {
    myLowerLimitActualTranslation = theLowerLimitActualTranslation;
  }
  else
    myLowerLimitActualTranslation = 0;

  defUpperLimitActualTranslation = hasUpperLimitActualTranslation;
  if (defUpperLimitActualTranslation)
  {
    myUpperLimitActualTranslation = theUpperLimitActualTranslation;
  }
  else
    myUpperLimitActualTranslation = 0;

  defLowerLimitActualRotation = hasLowerLimitActualRotation;
  if (defLowerLimitActualRotation)
  {
    myLowerLimitActualRotation = theLowerLimitActualRotation;
  }
  else
    myLowerLimitActualRotation = 0;

  defUpperLimitActualRotation = hasUpperLimitActualRotation;
  if (defUpperLimitActualRotation)
  {
    myUpperLimitActualRotation = theUpperLimitActualRotation;
  }
  else
    myUpperLimitActualRotation = 0;
}

//=================================================================================================

double StepKinematics_CylindricalPairWithRange::LowerLimitActualTranslation() const
{
  return myLowerLimitActualTranslation;
}

//=================================================================================================

void StepKinematics_CylindricalPairWithRange::SetLowerLimitActualTranslation(
  const double theLowerLimitActualTranslation)
{
  myLowerLimitActualTranslation = theLowerLimitActualTranslation;
}

//=================================================================================================

bool StepKinematics_CylindricalPairWithRange::HasLowerLimitActualTranslation() const
{
  return defLowerLimitActualTranslation;
}

//=================================================================================================

double StepKinematics_CylindricalPairWithRange::UpperLimitActualTranslation() const
{
  return myUpperLimitActualTranslation;
}

//=================================================================================================

void StepKinematics_CylindricalPairWithRange::SetUpperLimitActualTranslation(
  const double theUpperLimitActualTranslation)
{
  myUpperLimitActualTranslation = theUpperLimitActualTranslation;
}

//=================================================================================================

bool StepKinematics_CylindricalPairWithRange::HasUpperLimitActualTranslation() const
{
  return defUpperLimitActualTranslation;
}

//=================================================================================================

double StepKinematics_CylindricalPairWithRange::LowerLimitActualRotation() const
{
  return myLowerLimitActualRotation;
}

//=================================================================================================

void StepKinematics_CylindricalPairWithRange::SetLowerLimitActualRotation(
  const double theLowerLimitActualRotation)
{
  myLowerLimitActualRotation = theLowerLimitActualRotation;
}

//=================================================================================================

bool StepKinematics_CylindricalPairWithRange::HasLowerLimitActualRotation() const
{
  return defLowerLimitActualRotation;
}

//=================================================================================================

double StepKinematics_CylindricalPairWithRange::UpperLimitActualRotation() const
{
  return myUpperLimitActualRotation;
}

//=================================================================================================

void StepKinematics_CylindricalPairWithRange::SetUpperLimitActualRotation(
  const double theUpperLimitActualRotation)
{
  myUpperLimitActualRotation = theUpperLimitActualRotation;
}

//=================================================================================================

bool StepKinematics_CylindricalPairWithRange::HasUpperLimitActualRotation() const
{
  return defUpperLimitActualRotation;
}
