#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_LowOrderKinematicPairWithRange : public StepKinematics_LowOrderKinematicPair
{
public:
  Standard_EXPORT StepKinematics_LowOrderKinematicPairWithRange();

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
    const bool                                        hasLowerLimitActualRotationX,
    const double                                      theLowerLimitActualRotationX,
    const bool                                        hasUpperLimitActualRotationX,
    const double                                      theUpperLimitActualRotationX,
    const bool                                        hasLowerLimitActualRotationY,
    const double                                      theLowerLimitActualRotationY,
    const bool                                        hasUpperLimitActualRotationY,
    const double                                      theUpperLimitActualRotationY,
    const bool                                        hasLowerLimitActualRotationZ,
    const double                                      theLowerLimitActualRotationZ,
    const bool                                        hasUpperLimitActualRotationZ,
    const double                                      theUpperLimitActualRotationZ,
    const bool                                        hasLowerLimitActualTranslationX,
    const double                                      theLowerLimitActualTranslationX,
    const bool                                        hasUpperLimitActualTranslationX,
    const double                                      theUpperLimitActualTranslationX,
    const bool                                        hasLowerLimitActualTranslationY,
    const double                                      theLowerLimitActualTranslationY,
    const bool                                        hasUpperLimitActualTranslationY,
    const double                                      theUpperLimitActualTranslationY,
    const bool                                        hasLowerLimitActualTranslationZ,
    const double                                      theLowerLimitActualTranslationZ,
    const bool                                        hasUpperLimitActualTranslationZ,
    const double                                      theUpperLimitActualTranslationZ);

  Standard_EXPORT double LowerLimitActualRotationX() const;

  Standard_EXPORT void SetLowerLimitActualRotationX(const double theLowerLimitActualRotationX);

  Standard_EXPORT bool HasLowerLimitActualRotationX() const;

  Standard_EXPORT double UpperLimitActualRotationX() const;

  Standard_EXPORT void SetUpperLimitActualRotationX(const double theUpperLimitActualRotationX);

  Standard_EXPORT bool HasUpperLimitActualRotationX() const;

  Standard_EXPORT double LowerLimitActualRotationY() const;

  Standard_EXPORT void SetLowerLimitActualRotationY(const double theLowerLimitActualRotationY);

  Standard_EXPORT bool HasLowerLimitActualRotationY() const;

  Standard_EXPORT double UpperLimitActualRotationY() const;

  Standard_EXPORT void SetUpperLimitActualRotationY(const double theUpperLimitActualRotationY);

  Standard_EXPORT bool HasUpperLimitActualRotationY() const;

  Standard_EXPORT double LowerLimitActualRotationZ() const;

  Standard_EXPORT void SetLowerLimitActualRotationZ(const double theLowerLimitActualRotationZ);

  Standard_EXPORT bool HasLowerLimitActualRotationZ() const;

  Standard_EXPORT double UpperLimitActualRotationZ() const;

  Standard_EXPORT void SetUpperLimitActualRotationZ(const double theUpperLimitActualRotationZ);

  Standard_EXPORT bool HasUpperLimitActualRotationZ() const;

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

  Standard_EXPORT double LowerLimitActualTranslationZ() const;

  Standard_EXPORT void SetLowerLimitActualTranslationZ(
    const double theLowerLimitActualTranslationZ);

  Standard_EXPORT bool HasLowerLimitActualTranslationZ() const;

  Standard_EXPORT double UpperLimitActualTranslationZ() const;

  Standard_EXPORT void SetUpperLimitActualTranslationZ(
    const double theUpperLimitActualTranslationZ);

  Standard_EXPORT bool HasUpperLimitActualTranslationZ() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_LowOrderKinematicPairWithRange,
                          StepKinematics_LowOrderKinematicPair)

private:
  double myLowerLimitActualRotationX;
  double myUpperLimitActualRotationX;
  double myLowerLimitActualRotationY;
  double myUpperLimitActualRotationY;
  double myLowerLimitActualRotationZ;
  double myUpperLimitActualRotationZ;
  double myLowerLimitActualTranslationX;
  double myUpperLimitActualTranslationX;
  double myLowerLimitActualTranslationY;
  double myUpperLimitActualTranslationY;
  double myLowerLimitActualTranslationZ;
  double myUpperLimitActualTranslationZ;
  bool   defLowerLimitActualRotationX;
  bool   defUpperLimitActualRotationX;
  bool   defLowerLimitActualRotationY;
  bool   defUpperLimitActualRotationY;
  bool   defLowerLimitActualRotationZ;
  bool   defUpperLimitActualRotationZ;

  bool defLowerLimitActualTranslationX;
  bool defUpperLimitActualTranslationX;
  bool defLowerLimitActualTranslationY;
  bool defUpperLimitActualTranslationY;
  bool defLowerLimitActualTranslationZ;
  bool defUpperLimitActualTranslationZ;
};
