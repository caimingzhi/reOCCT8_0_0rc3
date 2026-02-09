#pragma once

#include <Standard.hpp>
#include <StepKinematics_PrismaticPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_PrismaticPairWithRange : public StepKinematics_PrismaticPair
{
public:
  Standard_EXPORT StepKinematics_PrismaticPairWithRange();

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
    const double                                      theUpperLimitActualTranslation);

  Standard_EXPORT double LowerLimitActualTranslation() const;

  Standard_EXPORT void SetLowerLimitActualTranslation(const double theLowerLimitActualTranslation);

  Standard_EXPORT bool HasLowerLimitActualTranslation() const;

  Standard_EXPORT double UpperLimitActualTranslation() const;

  Standard_EXPORT void SetUpperLimitActualTranslation(const double theUpperLimitActualTranslation);

  Standard_EXPORT bool HasUpperLimitActualTranslation() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PrismaticPairWithRange, StepKinematics_PrismaticPair)

private:
  double myLowerLimitActualTranslation;
  double myUpperLimitActualTranslation;

  bool defLowerLimitActualTranslation;
  bool defUpperLimitActualTranslation;
};
