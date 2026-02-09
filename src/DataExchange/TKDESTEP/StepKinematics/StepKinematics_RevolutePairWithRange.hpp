#pragma once

#include <Standard.hpp>
#include <StepKinematics_RevolutePair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_RevolutePairWithRange : public StepKinematics_RevolutePair
{
public:
  Standard_EXPORT StepKinematics_RevolutePairWithRange();

  Standard_EXPORT void Init(
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
    const double                                      theUpperLimitActualRotation);

  Standard_EXPORT double LowerLimitActualRotation() const;

  Standard_EXPORT void SetLowerLimitActualRotation(const double theLowerLimitActualRotation);

  Standard_EXPORT bool HasLowerLimitActualRotation() const;

  Standard_EXPORT double UpperLimitActualRotation() const;

  Standard_EXPORT void SetUpperLimitActualRotation(const double theUpperLimitActualRotation);

  Standard_EXPORT bool HasUpperLimitActualRotation() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RevolutePairWithRange, StepKinematics_RevolutePair)

private:
  double myLowerLimitActualRotation;
  double myUpperLimitActualRotation;
  bool   defLowerLimitActualRotation;
  bool   defUpperLimitActualRotation;
};
