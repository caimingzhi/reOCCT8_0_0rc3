#pragma once

#include <Standard.hpp>
#include <StepKinematics_ScrewPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_ScrewPairWithRange : public StepKinematics_ScrewPair
{
public:
  Standard_EXPORT StepKinematics_ScrewPairWithRange();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const double                                      theScrewPair_Pitch,
    const bool                                        hasLowerLimitActualRotation,
    const double                                      theLowerLimitActualRotation,
    const bool                                        hasUpperLimitActualRotation,
    const double                                      theUpperLimitActualRotation);

  Standard_EXPORT double LowerLimitActualRotation() const;

  Standard_EXPORT void SetLowerLimitActualRotation(const double theLowerLimitActualRotation);

  Standard_EXPORT bool HasLowerLimitActualRotation() const;

  Standard_EXPORT double UpperLimitActualRotation() const;

  Standard_EXPORT void SetUpperLimitActualRotation(const double theUpperLimitActualRotation);

  Standard_EXPORT bool HasUpperLimitActualRotation() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_ScrewPairWithRange, StepKinematics_ScrewPair)

private:
  double myLowerLimitActualRotation;
  double myUpperLimitActualRotation;
  bool   defLowerLimitActualRotation;
  bool   defUpperLimitActualRotation;
};
