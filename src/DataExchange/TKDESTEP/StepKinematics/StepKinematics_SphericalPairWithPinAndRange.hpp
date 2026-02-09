#pragma once

#include <Standard.hpp>
#include <StepKinematics_SphericalPairWithPin.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_SphericalPairWithPinAndRange : public StepKinematics_SphericalPairWithPin
{
public:
  Standard_EXPORT StepKinematics_SphericalPairWithPinAndRange();

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
    const bool                                        hasLowerLimitYaw,
    const double                                      theLowerLimitYaw,
    const bool                                        hasUpperLimitYaw,
    const double                                      theUpperLimitYaw,
    const bool                                        hasLowerLimitRoll,
    const double                                      theLowerLimitRoll,
    const bool                                        hasUpperLimitRoll,
    const double                                      theUpperLimitRoll);

  Standard_EXPORT double LowerLimitYaw() const;

  Standard_EXPORT void SetLowerLimitYaw(const double theLowerLimitYaw);

  Standard_EXPORT bool HasLowerLimitYaw() const;

  Standard_EXPORT double UpperLimitYaw() const;

  Standard_EXPORT void SetUpperLimitYaw(const double theUpperLimitYaw);

  Standard_EXPORT bool HasUpperLimitYaw() const;

  Standard_EXPORT double LowerLimitRoll() const;

  Standard_EXPORT void SetLowerLimitRoll(const double theLowerLimitRoll);

  Standard_EXPORT bool HasLowerLimitRoll() const;

  Standard_EXPORT double UpperLimitRoll() const;

  Standard_EXPORT void SetUpperLimitRoll(const double theUpperLimitRoll);

  Standard_EXPORT bool HasUpperLimitRoll() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SphericalPairWithPinAndRange,
                          StepKinematics_SphericalPairWithPin)

private:
  double myLowerLimitYaw;
  double myUpperLimitYaw;
  double myLowerLimitRoll;
  double myUpperLimitRoll;
  bool   defLowerLimitYaw;
  bool   defUpperLimitYaw;
  bool   defLowerLimitRoll;
  bool   defUpperLimitRoll;
};
