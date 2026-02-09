#pragma once

#include <Standard.hpp>
#include <StepKinematics_RackAndPinionPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_RackAndPinionPairWithRange : public StepKinematics_RackAndPinionPair
{
public:
  Standard_EXPORT StepKinematics_RackAndPinionPairWithRange();

  Standard_EXPORT void Init(
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
    const double                                      theUpperLimitRackDisplacement);

  Standard_EXPORT double LowerLimitRackDisplacement() const;

  Standard_EXPORT void SetLowerLimitRackDisplacement(const double theLowerLimitRackDisplacement);

  Standard_EXPORT bool HasLowerLimitRackDisplacement() const;

  Standard_EXPORT double UpperLimitRackDisplacement() const;

  Standard_EXPORT void SetUpperLimitRackDisplacement(const double theUpperLimitRackDisplacement);

  Standard_EXPORT bool HasUpperLimitRackDisplacement() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RackAndPinionPairWithRange,
                          StepKinematics_RackAndPinionPair)

private:
  double myLowerLimitRackDisplacement;
  double myUpperLimitRackDisplacement;

  bool defLowerLimitRackDisplacement;
  bool defUpperLimitRackDisplacement;
};
