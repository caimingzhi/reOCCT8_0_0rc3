#pragma once


#include <Standard.hpp>
#include <StepKinematics_CylindricalPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

//! Representation of STEP entity CylindricalPairWithRange
class StepKinematics_CylindricalPairWithRange : public StepKinematics_CylindricalPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_CylindricalPairWithRange();

  //! Initialize all fields (own and inherited)
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

  //! Returns field LowerLimitActualTranslation
  Standard_EXPORT double LowerLimitActualTranslation() const;
  //! Sets field LowerLimitActualTranslation
  Standard_EXPORT void SetLowerLimitActualTranslation(const double theLowerLimitActualTranslation);
  //! Returns True if optional field LowerLimitActualTranslation is defined
  Standard_EXPORT bool HasLowerLimitActualTranslation() const;

  //! Returns field UpperLimitActualTranslation
  Standard_EXPORT double UpperLimitActualTranslation() const;
  //! Sets field UpperLimitActualTranslation
  Standard_EXPORT void SetUpperLimitActualTranslation(const double theUpperLimitActualTranslation);
  //! Returns True if optional field UpperLimitActualTranslation is defined
  Standard_EXPORT bool HasUpperLimitActualTranslation() const;

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

  DEFINE_STANDARD_RTTIEXT(StepKinematics_CylindricalPairWithRange, StepKinematics_CylindricalPair)

private:
  double myLowerLimitActualTranslation; //!< optional
  double myUpperLimitActualTranslation; //!< optional
  double myLowerLimitActualRotation;    //!< optional
  double myUpperLimitActualRotation;    //!< optional
                                        // clang-format off
  bool defLowerLimitActualTranslation; //!< flag "is LowerLimitActualTranslation defined"
  bool defUpperLimitActualTranslation; //!< flag "is UpperLimitActualTranslation defined"
                                        // clang-format on
  bool defLowerLimitActualRotation;     //!< flag "is LowerLimitActualRotation defined"
  bool defUpperLimitActualRotation;     //!< flag "is UpperLimitActualRotation defined"
};
