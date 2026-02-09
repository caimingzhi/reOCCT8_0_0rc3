#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPairWithMotionCoupling.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_GearPair : public StepKinematics_LowOrderKinematicPairWithMotionCoupling
{
public:
  Standard_EXPORT StepKinematics_GearPair();

  Standard_EXPORT void Init(
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
    const double                                      theGearRatio);

  Standard_EXPORT double RadiusFirstLink() const;

  Standard_EXPORT void SetRadiusFirstLink(const double theRadiusFirstLink);

  Standard_EXPORT double RadiusSecondLink() const;

  Standard_EXPORT void SetRadiusSecondLink(const double theRadiusSecondLink);

  Standard_EXPORT double Bevel() const;

  Standard_EXPORT void SetBevel(const double theBevel);

  Standard_EXPORT double HelicalAngle() const;

  Standard_EXPORT void SetHelicalAngle(const double theHelicalAngle);

  Standard_EXPORT double GearRatio() const;

  Standard_EXPORT void SetGearRatio(const double theGearRatio);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_GearPair,
                          StepKinematics_LowOrderKinematicPairWithMotionCoupling)

private:
  double myRadiusFirstLink;
  double myRadiusSecondLink;
  double myBevel;
  double myHelicalAngle;
  double myGearRatio;
};
