

#include <StepKinematics_GearPair.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_GearPair,
                           StepKinematics_LowOrderKinematicPairWithMotionCoupling)

StepKinematics_GearPair::StepKinematics_GearPair() = default;

void StepKinematics_GearPair::Init(
  const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
  const bool                                        hasItemDefinedTransformation_Description,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
  const double                                      theRadiusFirstLink,
  const double                                      theRadiusSecondLink,
  const double                                      theBevel,
  const double                                      theHelicalAngle,
  const double                                      theGearRatio)
{
  StepKinematics_LowOrderKinematicPairWithMotionCoupling::Init(
    theRepresentationItem_Name,
    theItemDefinedTransformation_Name,
    hasItemDefinedTransformation_Description,
    theItemDefinedTransformation_Description,
    theItemDefinedTransformation_TransformItem1,
    theItemDefinedTransformation_TransformItem2,
    theKinematicPair_Joint);

  myRadiusFirstLink = theRadiusFirstLink;

  myRadiusSecondLink = theRadiusSecondLink;

  myBevel = theBevel;

  myHelicalAngle = theHelicalAngle;

  myGearRatio = theGearRatio;
}

double StepKinematics_GearPair::RadiusFirstLink() const
{
  return myRadiusFirstLink;
}

void StepKinematics_GearPair::SetRadiusFirstLink(const double theRadiusFirstLink)
{
  myRadiusFirstLink = theRadiusFirstLink;
}

double StepKinematics_GearPair::RadiusSecondLink() const
{
  return myRadiusSecondLink;
}

void StepKinematics_GearPair::SetRadiusSecondLink(const double theRadiusSecondLink)
{
  myRadiusSecondLink = theRadiusSecondLink;
}

double StepKinematics_GearPair::Bevel() const
{
  return myBevel;
}

void StepKinematics_GearPair::SetBevel(const double theBevel)
{
  myBevel = theBevel;
}

double StepKinematics_GearPair::HelicalAngle() const
{
  return myHelicalAngle;
}

void StepKinematics_GearPair::SetHelicalAngle(const double theHelicalAngle)
{
  myHelicalAngle = theHelicalAngle;
}

double StepKinematics_GearPair::GearRatio() const
{
  return myGearRatio;
}

void StepKinematics_GearPair::SetGearRatio(const double theGearRatio)
{
  myGearRatio = theGearRatio;
}
