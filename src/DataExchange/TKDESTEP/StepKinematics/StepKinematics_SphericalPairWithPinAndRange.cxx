

#include <StepKinematics_SphericalPairWithPinAndRange.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_SphericalPairWithPinAndRange,
                           StepKinematics_SphericalPairWithPin)

StepKinematics_SphericalPairWithPinAndRange::StepKinematics_SphericalPairWithPinAndRange()
{
  defLowerLimitYaw  = false;
  defUpperLimitYaw  = false;
  defLowerLimitRoll = false;
  defUpperLimitRoll = false;
}

void StepKinematics_SphericalPairWithPinAndRange::Init(
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
  const bool                                        hasLowerLimitYaw,
  const double                                      theLowerLimitYaw,
  const bool                                        hasUpperLimitYaw,
  const double                                      theUpperLimitYaw,
  const bool                                        hasLowerLimitRoll,
  const double                                      theLowerLimitRoll,
  const bool                                        hasUpperLimitRoll,
  const double                                      theUpperLimitRoll)
{
  StepKinematics_SphericalPairWithPin::Init(theRepresentationItem_Name,
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

  defLowerLimitYaw = hasLowerLimitYaw;
  if (defLowerLimitYaw)
  {
    myLowerLimitYaw = theLowerLimitYaw;
  }
  else
    myLowerLimitYaw = 0;

  defUpperLimitYaw = hasUpperLimitYaw;
  if (defUpperLimitYaw)
  {
    myUpperLimitYaw = theUpperLimitYaw;
  }
  else
    myUpperLimitYaw = 0;

  defLowerLimitRoll = hasLowerLimitRoll;
  if (defLowerLimitRoll)
  {
    myLowerLimitRoll = theLowerLimitRoll;
  }
  else
    myLowerLimitRoll = 0;

  defUpperLimitRoll = hasUpperLimitRoll;
  if (defUpperLimitRoll)
  {
    myUpperLimitRoll = theUpperLimitRoll;
  }
  else
    myUpperLimitRoll = 0;
}

double StepKinematics_SphericalPairWithPinAndRange::LowerLimitYaw() const
{
  return myLowerLimitYaw;
}

void StepKinematics_SphericalPairWithPinAndRange::SetLowerLimitYaw(const double theLowerLimitYaw)
{
  myLowerLimitYaw = theLowerLimitYaw;
}

bool StepKinematics_SphericalPairWithPinAndRange::HasLowerLimitYaw() const
{
  return defLowerLimitYaw;
}

double StepKinematics_SphericalPairWithPinAndRange::UpperLimitYaw() const
{
  return myUpperLimitYaw;
}

void StepKinematics_SphericalPairWithPinAndRange::SetUpperLimitYaw(const double theUpperLimitYaw)
{
  myUpperLimitYaw = theUpperLimitYaw;
}

bool StepKinematics_SphericalPairWithPinAndRange::HasUpperLimitYaw() const
{
  return defUpperLimitYaw;
}

double StepKinematics_SphericalPairWithPinAndRange::LowerLimitRoll() const
{
  return myLowerLimitRoll;
}

void StepKinematics_SphericalPairWithPinAndRange::SetLowerLimitRoll(const double theLowerLimitRoll)
{
  myLowerLimitRoll = theLowerLimitRoll;
}

bool StepKinematics_SphericalPairWithPinAndRange::HasLowerLimitRoll() const
{
  return defLowerLimitRoll;
}

double StepKinematics_SphericalPairWithPinAndRange::UpperLimitRoll() const
{
  return myUpperLimitRoll;
}

void StepKinematics_SphericalPairWithPinAndRange::SetUpperLimitRoll(const double theUpperLimitRoll)
{
  myUpperLimitRoll = theUpperLimitRoll;
}

bool StepKinematics_SphericalPairWithPinAndRange::HasUpperLimitRoll() const
{
  return defUpperLimitRoll;
}
