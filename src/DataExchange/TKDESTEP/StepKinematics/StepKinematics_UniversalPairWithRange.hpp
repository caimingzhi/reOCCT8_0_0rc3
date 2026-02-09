#pragma once

#include <Standard.hpp>
#include <StepKinematics_UniversalPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_UniversalPairWithRange : public StepKinematics_UniversalPair
{
public:
  Standard_EXPORT StepKinematics_UniversalPairWithRange();

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
    const bool                                        hasUniversalPair_InputSkewAngle,
    const double                                      theUniversalPair_InputSkewAngle,
    const bool                                        hasLowerLimitFirstRotation,
    const double                                      theLowerLimitFirstRotation,
    const bool                                        hasUpperLimitFirstRotation,
    const double                                      theUpperLimitFirstRotation,
    const bool                                        hasLowerLimitSecondRotation,
    const double                                      theLowerLimitSecondRotation,
    const bool                                        hasUpperLimitSecondRotation,
    const double                                      theUpperLimitSecondRotation);

  Standard_EXPORT double LowerLimitFirstRotation() const;

  Standard_EXPORT void SetLowerLimitFirstRotation(const double theLowerLimitFirstRotation);

  Standard_EXPORT bool HasLowerLimitFirstRotation() const;

  Standard_EXPORT double UpperLimitFirstRotation() const;

  Standard_EXPORT void SetUpperLimitFirstRotation(const double theUpperLimitFirstRotation);

  Standard_EXPORT bool HasUpperLimitFirstRotation() const;

  Standard_EXPORT double LowerLimitSecondRotation() const;

  Standard_EXPORT void SetLowerLimitSecondRotation(const double theLowerLimitSecondRotation);

  Standard_EXPORT bool HasLowerLimitSecondRotation() const;

  Standard_EXPORT double UpperLimitSecondRotation() const;

  Standard_EXPORT void SetUpperLimitSecondRotation(const double theUpperLimitSecondRotation);

  Standard_EXPORT bool HasUpperLimitSecondRotation() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_UniversalPairWithRange, StepKinematics_UniversalPair)

private:
  double myLowerLimitFirstRotation;
  double myUpperLimitFirstRotation;
  double myLowerLimitSecondRotation;
  double myUpperLimitSecondRotation;
  bool   defLowerLimitFirstRotation;
  bool   defUpperLimitFirstRotation;
  bool   defLowerLimitSecondRotation;
  bool   defUpperLimitSecondRotation;
};
