#pragma once


#include <Standard.hpp>
#include <StepKinematics_ScrewPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

//! Representation of STEP entity ScrewPairWithRange
class StepKinematics_ScrewPairWithRange : public StepKinematics_ScrewPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_ScrewPairWithRange();

  //! Initialize all fields (own and inherited)
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

  //! Returns field LowerLimitActualRotation
  Standard_EXPORT double LowerLimitActualRotation() const;
  //! Sets field LowerLimitActualRotation
  Standard_EXPORT void SetLowerLimitActualRotation(const double theLowerLimitActualRotation);
  //! Returns True if optional field LowerLimitActualRotation is defined
  Standard_EXPORT bool HasLowerLimitActualRotation() const;

  //! Returns field UpperLimitActualRotation
  Standard_EXPORT double UpperLimitActualRotation() const;
  //! Sets field UpperLimitActualRotation
  Standard_EXPORT void SetUpperLimitActualRotation(const double theUpperLimitActualRotation);
  //! Returns True if optional field UpperLimitActualRotation is defined
  Standard_EXPORT bool HasUpperLimitActualRotation() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_ScrewPairWithRange, StepKinematics_ScrewPair)

private:
  double myLowerLimitActualRotation;  //!< optional
  double myUpperLimitActualRotation;  //!< optional
  bool   defLowerLimitActualRotation; //!< flag "is LowerLimitActualRotation defined"
  bool   defUpperLimitActualRotation; //!< flag "is UpperLimitActualRotation defined"
};
