#pragma once

#include <Standard.hpp>
#include <StepKinematics_CylindricalPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_CylindricalPairWithRange : public StepKinematics_CylindricalPair
{
public:
  Standard_EXPORT StepKinematics_CylindricalPairWithRange();

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
    const bool                                        hasLowerLimitActualTranslation,
    const double                                      theLowerLimitActualTranslation,
    const bool                                        hasUpperLimitActualTranslation,
    const double                                      theUpperLimitActualTranslation,
    const bool                                        hasLowerLimitActualRotation,
    const double                                      theLowerLimitActualRotation,
    const bool                                        hasUpperLimitActualRotation,
    const double                                      theUpperLimitActualRotation);

  Standard_EXPORT double LowerLimitActualTranslation() const;

  Standard_EXPORT void SetLowerLimitActualTranslation(const double theLowerLimitActualTranslation);

  Standard_EXPORT bool HasLowerLimitActualTranslation() const;

  Standard_EXPORT double UpperLimitActualTranslation() const;

  Standard_EXPORT void SetUpperLimitActualTranslation(const double theUpperLimitActualTranslation);

  Standard_EXPORT bool HasUpperLimitActualTranslation() const;

  Standard_EXPORT double LowerLimitActualRotation() const;

  Standard_EXPORT void SetLowerLimitActualRotation(const double theLowerLimitActualRotation);

  Standard_EXPORT bool HasLowerLimitActualRotation() const;

  Standard_EXPORT double UpperLimitActualRotation() const;

  Standard_EXPORT void SetUpperLimitActualRotation(const double theUpperLimitActualRotation);

  Standard_EXPORT bool HasUpperLimitActualRotation() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_CylindricalPairWithRange, StepKinematics_CylindricalPair)

private:
  double myLowerLimitActualTranslation;
  double myUpperLimitActualTranslation;
  double myLowerLimitActualRotation;
  double myUpperLimitActualRotation;

  bool defLowerLimitActualTranslation;
  bool defUpperLimitActualTranslation;

  bool defLowerLimitActualRotation;
  bool defUpperLimitActualRotation;
};
