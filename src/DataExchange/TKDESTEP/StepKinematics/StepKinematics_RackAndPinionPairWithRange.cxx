// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_RackAndPinionPairWithRange.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_RackAndPinionPairWithRange,
                           StepKinematics_RackAndPinionPair)

//=================================================================================================

StepKinematics_RackAndPinionPairWithRange::StepKinematics_RackAndPinionPairWithRange()
{
  defLowerLimitRackDisplacement = false;
  defUpperLimitRackDisplacement = false;
}

//=================================================================================================

void StepKinematics_RackAndPinionPairWithRange::Init(
  const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
  const bool                                        hasItemDefinedTransformation_Description,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
  const double                                      theRackAndPinionPair_PinionRadius,
  const bool                                        hasLowerLimitRackDisplacement,
  const double                                      theLowerLimitRackDisplacement,
  const bool                                        hasUpperLimitRackDisplacement,
  const double                                      theUpperLimitRackDisplacement)
{
  StepKinematics_RackAndPinionPair::Init(theRepresentationItem_Name,
                                         theItemDefinedTransformation_Name,
                                         hasItemDefinedTransformation_Description,
                                         theItemDefinedTransformation_Description,
                                         theItemDefinedTransformation_TransformItem1,
                                         theItemDefinedTransformation_TransformItem2,
                                         theKinematicPair_Joint,
                                         theRackAndPinionPair_PinionRadius);

  defLowerLimitRackDisplacement = hasLowerLimitRackDisplacement;
  if (defLowerLimitRackDisplacement)
  {
    myLowerLimitRackDisplacement = theLowerLimitRackDisplacement;
  }
  else
    myLowerLimitRackDisplacement = 0;

  defUpperLimitRackDisplacement = hasUpperLimitRackDisplacement;
  if (defUpperLimitRackDisplacement)
  {
    myUpperLimitRackDisplacement = theUpperLimitRackDisplacement;
  }
  else
    myUpperLimitRackDisplacement = 0;
}

//=================================================================================================

double StepKinematics_RackAndPinionPairWithRange::LowerLimitRackDisplacement() const
{
  return myLowerLimitRackDisplacement;
}

//=================================================================================================

void StepKinematics_RackAndPinionPairWithRange::SetLowerLimitRackDisplacement(
  const double theLowerLimitRackDisplacement)
{
  myLowerLimitRackDisplacement = theLowerLimitRackDisplacement;
}

//=================================================================================================

bool StepKinematics_RackAndPinionPairWithRange::HasLowerLimitRackDisplacement() const
{
  return defLowerLimitRackDisplacement;
}

//=================================================================================================

double StepKinematics_RackAndPinionPairWithRange::UpperLimitRackDisplacement() const
{
  return myUpperLimitRackDisplacement;
}

//=================================================================================================

void StepKinematics_RackAndPinionPairWithRange::SetUpperLimitRackDisplacement(
  const double theUpperLimitRackDisplacement)
{
  myUpperLimitRackDisplacement = theUpperLimitRackDisplacement;
}

//=================================================================================================

bool StepKinematics_RackAndPinionPairWithRange::HasUpperLimitRackDisplacement() const
{
  return defUpperLimitRackDisplacement;
}
