

#include <StepKinematics_PlanarPairWithRange.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PlanarPairWithRange, StepKinematics_PlanarPair)

StepKinematics_PlanarPairWithRange::StepKinematics_PlanarPairWithRange()
{
  defLowerLimitActualRotation     = false;
  defUpperLimitActualRotation     = false;
  defLowerLimitActualTranslationX = false;
  defUpperLimitActualTranslationX = false;
  defLowerLimitActualTranslationY = false;
  defUpperLimitActualTranslationY = false;
}

void StepKinematics_PlanarPairWithRange::Init(
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
  const bool                                        hasLowerLimitActualRotation,
  const double                                      theLowerLimitActualRotation,
  const bool                                        hasUpperLimitActualRotation,
  const double                                      theUpperLimitActualRotation,
  const bool                                        hasLowerLimitActualTranslationX,
  const double                                      theLowerLimitActualTranslationX,
  const bool                                        hasUpperLimitActualTranslationX,
  const double                                      theUpperLimitActualTranslationX,
  const bool                                        hasLowerLimitActualTranslationY,
  const double                                      theLowerLimitActualTranslationY,
  const bool                                        hasUpperLimitActualTranslationY,
  const double                                      theUpperLimitActualTranslationY)
{
  StepKinematics_PlanarPair::Init(theRepresentationItem_Name,
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

  defLowerLimitActualTranslationX = hasLowerLimitActualTranslationX;
  if (defLowerLimitActualTranslationX)
  {
    myLowerLimitActualTranslationX = theLowerLimitActualTranslationX;
  }
  else
    myLowerLimitActualTranslationX = 0;

  defUpperLimitActualTranslationX = hasUpperLimitActualTranslationX;
  if (defUpperLimitActualTranslationX)
  {
    myUpperLimitActualTranslationX = theUpperLimitActualTranslationX;
  }
  else
    myUpperLimitActualTranslationX = 0;

  defLowerLimitActualTranslationY = hasLowerLimitActualTranslationY;
  if (defLowerLimitActualTranslationY)
  {
    myLowerLimitActualTranslationY = theLowerLimitActualTranslationY;
  }
  else
    myLowerLimitActualTranslationY = 0;

  defUpperLimitActualTranslationY = hasUpperLimitActualTranslationY;
  if (defUpperLimitActualTranslationY)
  {
    myUpperLimitActualTranslationY = theUpperLimitActualTranslationY;
  }
  else
    myUpperLimitActualTranslationY = 0;
}

double StepKinematics_PlanarPairWithRange::LowerLimitActualRotation() const
{
  return myLowerLimitActualRotation;
}

void StepKinematics_PlanarPairWithRange::SetLowerLimitActualRotation(
  const double theLowerLimitActualRotation)
{
  myLowerLimitActualRotation = theLowerLimitActualRotation;
}

bool StepKinematics_PlanarPairWithRange::HasLowerLimitActualRotation() const
{
  return defLowerLimitActualRotation;
}

double StepKinematics_PlanarPairWithRange::UpperLimitActualRotation() const
{
  return myUpperLimitActualRotation;
}

void StepKinematics_PlanarPairWithRange::SetUpperLimitActualRotation(
  const double theUpperLimitActualRotation)
{
  myUpperLimitActualRotation = theUpperLimitActualRotation;
}

bool StepKinematics_PlanarPairWithRange::HasUpperLimitActualRotation() const
{
  return defUpperLimitActualRotation;
}

double StepKinematics_PlanarPairWithRange::LowerLimitActualTranslationX() const
{
  return myLowerLimitActualTranslationX;
}

void StepKinematics_PlanarPairWithRange::SetLowerLimitActualTranslationX(
  const double theLowerLimitActualTranslationX)
{
  myLowerLimitActualTranslationX = theLowerLimitActualTranslationX;
}

bool StepKinematics_PlanarPairWithRange::HasLowerLimitActualTranslationX() const
{
  return defLowerLimitActualTranslationX;
}

double StepKinematics_PlanarPairWithRange::UpperLimitActualTranslationX() const
{
  return myUpperLimitActualTranslationX;
}

void StepKinematics_PlanarPairWithRange::SetUpperLimitActualTranslationX(
  const double theUpperLimitActualTranslationX)
{
  myUpperLimitActualTranslationX = theUpperLimitActualTranslationX;
}

bool StepKinematics_PlanarPairWithRange::HasUpperLimitActualTranslationX() const
{
  return defUpperLimitActualTranslationX;
}

double StepKinematics_PlanarPairWithRange::LowerLimitActualTranslationY() const
{
  return myLowerLimitActualTranslationY;
}

void StepKinematics_PlanarPairWithRange::SetLowerLimitActualTranslationY(
  const double theLowerLimitActualTranslationY)
{
  myLowerLimitActualTranslationY = theLowerLimitActualTranslationY;
}

bool StepKinematics_PlanarPairWithRange::HasLowerLimitActualTranslationY() const
{
  return defLowerLimitActualTranslationY;
}

double StepKinematics_PlanarPairWithRange::UpperLimitActualTranslationY() const
{
  return myUpperLimitActualTranslationY;
}

void StepKinematics_PlanarPairWithRange::SetUpperLimitActualTranslationY(
  const double theUpperLimitActualTranslationY)
{
  myUpperLimitActualTranslationY = theUpperLimitActualTranslationY;
}

bool StepKinematics_PlanarPairWithRange::HasUpperLimitActualTranslationY() const
{
  return defUpperLimitActualTranslationY;
}
