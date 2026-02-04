#pragma once


#include <Standard.hpp>
#include <StepKinematics_SphericalPairWithPin.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

//! Representation of STEP entity SphericalPairWithPinAndRange
class StepKinematics_SphericalPairWithPinAndRange : public StepKinematics_SphericalPairWithPin
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_SphericalPairWithPinAndRange();

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
    const bool                                        hasLowerLimitYaw,
    const double                                      theLowerLimitYaw,
    const bool                                        hasUpperLimitYaw,
    const double                                      theUpperLimitYaw,
    const bool                                        hasLowerLimitRoll,
    const double                                      theLowerLimitRoll,
    const bool                                        hasUpperLimitRoll,
    const double                                      theUpperLimitRoll);

  //! Returns field LowerLimitYaw
  Standard_EXPORT double LowerLimitYaw() const;
  //! Sets field LowerLimitYaw
  Standard_EXPORT void SetLowerLimitYaw(const double theLowerLimitYaw);
  //! Returns True if optional field LowerLimitYaw is defined
  Standard_EXPORT bool HasLowerLimitYaw() const;

  //! Returns field UpperLimitYaw
  Standard_EXPORT double UpperLimitYaw() const;
  //! Sets field UpperLimitYaw
  Standard_EXPORT void SetUpperLimitYaw(const double theUpperLimitYaw);
  //! Returns True if optional field UpperLimitYaw is defined
  Standard_EXPORT bool HasUpperLimitYaw() const;

  //! Returns field LowerLimitRoll
  Standard_EXPORT double LowerLimitRoll() const;
  //! Sets field LowerLimitRoll
  Standard_EXPORT void SetLowerLimitRoll(const double theLowerLimitRoll);
  //! Returns True if optional field LowerLimitRoll is defined
  Standard_EXPORT bool HasLowerLimitRoll() const;

  //! Returns field UpperLimitRoll
  Standard_EXPORT double UpperLimitRoll() const;
  //! Sets field UpperLimitRoll
  Standard_EXPORT void SetUpperLimitRoll(const double theUpperLimitRoll);
  //! Returns True if optional field UpperLimitRoll is defined
  Standard_EXPORT bool HasUpperLimitRoll() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SphericalPairWithPinAndRange,
                          StepKinematics_SphericalPairWithPin)

private:
  double myLowerLimitYaw;   //!< optional
  double myUpperLimitYaw;   //!< optional
  double myLowerLimitRoll;  //!< optional
  double myUpperLimitRoll;  //!< optional
  bool   defLowerLimitYaw;  //!< flag "is LowerLimitYaw defined"
  bool   defUpperLimitYaw;  //!< flag "is UpperLimitYaw defined"
  bool   defLowerLimitRoll; //!< flag "is LowerLimitRoll defined"
  bool   defUpperLimitRoll; //!< flag "is UpperLimitRoll defined"
};
