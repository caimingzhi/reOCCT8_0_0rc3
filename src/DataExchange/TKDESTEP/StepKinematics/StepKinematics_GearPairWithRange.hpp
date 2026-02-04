#pragma once


#include <Standard.hpp>
#include <StepKinematics_GearPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

//! Representation of STEP entity GearPairWithRange
class StepKinematics_GearPairWithRange : public StepKinematics_GearPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_GearPairWithRange();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const double                                      theGearPair_RadiusFirstLink,
    const double                                      theGearPair_RadiusSecondLink,
    const double                                      theGearPair_Bevel,
    const double                                      theGearPair_HelicalAngle,
    const double                                      theGearPair_GearRatio,
    const bool                                        hasLowerLimitActualRotation1,
    const double                                      theLowerLimitActualRotation1,
    const bool                                        hasUpperLimitActualRotation1,
    const double                                      theUpperLimitActualRotation1);

  //! Returns field LowerLimitActualRotation1
  Standard_EXPORT double LowerLimitActualRotation1() const;
  //! Sets field LowerLimitActualRotation1
  Standard_EXPORT void SetLowerLimitActualRotation1(const double theLowerLimitActualRotation1);
  //! Returns True if optional field LowerLimitActualRotation1 is defined
  Standard_EXPORT bool HasLowerLimitActualRotation1() const;

  //! Returns field UpperLimitActualRotation1
  Standard_EXPORT double UpperLimitActualRotation1() const;
  //! Sets field UpperLimitActualRotation1
  Standard_EXPORT void SetUpperLimitActualRotation1(const double theUpperLimitActualRotation1);
  //! Returns True if optional field UpperLimitActualRotation1 is defined
  Standard_EXPORT bool HasUpperLimitActualRotation1() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_GearPairWithRange, StepKinematics_GearPair)

private:
  double myLowerLimitActualRotation1;  //!< optional
  double myUpperLimitActualRotation1;  //!< optional
  bool   defLowerLimitActualRotation1; //!< flag "is LowerLimitActualRotation1 defined"
  bool   defUpperLimitActualRotation1; //!< flag "is UpperLimitActualRotation1 defined"
};
