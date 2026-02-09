#pragma once

#include <Standard.hpp>
#include <StepKinematics_PlanarPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_PlanarPairWithRange : public StepKinematics_PlanarPair
{
public:
  Standard_EXPORT StepKinematics_PlanarPairWithRange();

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
    const double                                      theUpperLimitActualRotation,
    const bool                                        hasLowerLimitActualTranslationX,
    const double                                      theLowerLimitActualTranslationX,
    const bool                                        hasUpperLimitActualTranslationX,
    const double                                      theUpperLimitActualTranslationX,
    const bool                                        hasLowerLimitActualTranslationY,
    const double                                      theLowerLimitActualTranslationY,
    const bool                                        hasUpperLimitActualTranslationY,
    const double                                      theUpperLimitActualTranslationY);

  Standard_EXPORT double LowerLimitActualRotation() const;

  Standard_EXPORT void SetLowerLimitActualRotation(const double theLowerLimitActualRotation);

  Standard_EXPORT bool HasLowerLimitActualRotation() const;

  Standard_EXPORT double UpperLimitActualRotation() const;

  Standard_EXPORT void SetUpperLimitActualRotation(const double theUpperLimitActualRotation);

  Standard_EXPORT bool HasUpperLimitActualRotation() const;

  Standard_EXPORT double LowerLimitActualTranslationX() const;

  Standard_EXPORT void SetLowerLimitActualTranslationX(
    const double theLowerLimitActualTranslationX);

  Standard_EXPORT bool HasLowerLimitActualTranslationX() const;

  Standard_EXPORT double UpperLimitActualTranslationX() const;

  Standard_EXPORT void SetUpperLimitActualTranslationX(
    const double theUpperLimitActualTranslationX);

  Standard_EXPORT bool HasUpperLimitActualTranslationX() const;

  Standard_EXPORT double LowerLimitActualTranslationY() const;

  Standard_EXPORT void SetLowerLimitActualTranslationY(
    const double theLowerLimitActualTranslationY);

  Standard_EXPORT bool HasLowerLimitActualTranslationY() const;

  Standard_EXPORT double UpperLimitActualTranslationY() const;

  Standard_EXPORT void SetUpperLimitActualTranslationY(
    const double theUpperLimitActualTranslationY);

  Standard_EXPORT bool HasUpperLimitActualTranslationY() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PlanarPairWithRange, StepKinematics_PlanarPair)

private:
  double myLowerLimitActualRotation;
  double myUpperLimitActualRotation;
  double myLowerLimitActualTranslationX;
  double myUpperLimitActualTranslationX;
  double myLowerLimitActualTranslationY;
  double myUpperLimitActualTranslationY;
  bool   defLowerLimitActualRotation;
  bool   defUpperLimitActualRotation;

  bool defLowerLimitActualTranslationX;
  bool defUpperLimitActualTranslationX;
  bool defLowerLimitActualTranslationY;
  bool defUpperLimitActualTranslationY;
};
