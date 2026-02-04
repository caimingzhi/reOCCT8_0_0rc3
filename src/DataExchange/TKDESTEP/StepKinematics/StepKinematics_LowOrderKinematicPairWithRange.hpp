#pragma once


#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

//! Representation of STEP entity LowOrderKinematicPairWithRange
class StepKinematics_LowOrderKinematicPairWithRange : public StepKinematics_LowOrderKinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_LowOrderKinematicPairWithRange();

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

  //! Returns field LowerLimitActualRotationX
  Standard_EXPORT double LowerLimitActualRotationX() const;
  //! Sets field LowerLimitActualRotationX
  Standard_EXPORT void SetLowerLimitActualRotationX(const double theLowerLimitActualRotationX);
  //! Returns True if optional field LowerLimitActualRotationX is defined
  Standard_EXPORT bool HasLowerLimitActualRotationX() const;

  //! Returns field UpperLimitActualRotationX
  Standard_EXPORT double UpperLimitActualRotationX() const;
  //! Sets field UpperLimitActualRotationX
  Standard_EXPORT void SetUpperLimitActualRotationX(const double theUpperLimitActualRotationX);
  //! Returns True if optional field UpperLimitActualRotationX is defined
  Standard_EXPORT bool HasUpperLimitActualRotationX() const;

  //! Returns field LowerLimitActualRotationY
  Standard_EXPORT double LowerLimitActualRotationY() const;
  //! Sets field LowerLimitActualRotationY
  Standard_EXPORT void SetLowerLimitActualRotationY(const double theLowerLimitActualRotationY);
  //! Returns True if optional field LowerLimitActualRotationY is defined
  Standard_EXPORT bool HasLowerLimitActualRotationY() const;

  //! Returns field UpperLimitActualRotationY
  Standard_EXPORT double UpperLimitActualRotationY() const;
  //! Sets field UpperLimitActualRotationY
  Standard_EXPORT void SetUpperLimitActualRotationY(const double theUpperLimitActualRotationY);
  //! Returns True if optional field UpperLimitActualRotationY is defined
  Standard_EXPORT bool HasUpperLimitActualRotationY() const;

  //! Returns field LowerLimitActualRotationZ
  Standard_EXPORT double LowerLimitActualRotationZ() const;
  //! Sets field LowerLimitActualRotationZ
  Standard_EXPORT void SetLowerLimitActualRotationZ(const double theLowerLimitActualRotationZ);
  //! Returns True if optional field LowerLimitActualRotationZ is defined
  Standard_EXPORT bool HasLowerLimitActualRotationZ() const;

  //! Returns field UpperLimitActualRotationZ
  Standard_EXPORT double UpperLimitActualRotationZ() const;
  //! Sets field UpperLimitActualRotationZ
  Standard_EXPORT void SetUpperLimitActualRotationZ(const double theUpperLimitActualRotationZ);
  //! Returns True if optional field UpperLimitActualRotationZ is defined
  Standard_EXPORT bool HasUpperLimitActualRotationZ() const;

  //! Returns field LowerLimitActualTranslationX
  Standard_EXPORT double LowerLimitActualTranslationX() const;
  //! Sets field LowerLimitActualTranslationX
  Standard_EXPORT void SetLowerLimitActualTranslationX(
    const double theLowerLimitActualTranslationX);
  //! Returns True if optional field LowerLimitActualTranslationX is defined
  Standard_EXPORT bool HasLowerLimitActualTranslationX() const;

  //! Returns field UpperLimitActualTranslationX
  Standard_EXPORT double UpperLimitActualTranslationX() const;
  //! Sets field UpperLimitActualTranslationX
  Standard_EXPORT void SetUpperLimitActualTranslationX(
    const double theUpperLimitActualTranslationX);
  //! Returns True if optional field UpperLimitActualTranslationX is defined
  Standard_EXPORT bool HasUpperLimitActualTranslationX() const;

  //! Returns field LowerLimitActualTranslationY
  Standard_EXPORT double LowerLimitActualTranslationY() const;
  //! Sets field LowerLimitActualTranslationY
  Standard_EXPORT void SetLowerLimitActualTranslationY(
    const double theLowerLimitActualTranslationY);
  //! Returns True if optional field LowerLimitActualTranslationY is defined
  Standard_EXPORT bool HasLowerLimitActualTranslationY() const;

  //! Returns field UpperLimitActualTranslationY
  Standard_EXPORT double UpperLimitActualTranslationY() const;
  //! Sets field UpperLimitActualTranslationY
  Standard_EXPORT void SetUpperLimitActualTranslationY(
    const double theUpperLimitActualTranslationY);
  //! Returns True if optional field UpperLimitActualTranslationY is defined
  Standard_EXPORT bool HasUpperLimitActualTranslationY() const;

  //! Returns field LowerLimitActualTranslationZ
  Standard_EXPORT double LowerLimitActualTranslationZ() const;
  //! Sets field LowerLimitActualTranslationZ
  Standard_EXPORT void SetLowerLimitActualTranslationZ(
    const double theLowerLimitActualTranslationZ);
  //! Returns True if optional field LowerLimitActualTranslationZ is defined
  Standard_EXPORT bool HasLowerLimitActualTranslationZ() const;

  //! Returns field UpperLimitActualTranslationZ
  Standard_EXPORT double UpperLimitActualTranslationZ() const;
  //! Sets field UpperLimitActualTranslationZ
  Standard_EXPORT void SetUpperLimitActualTranslationZ(
    const double theUpperLimitActualTranslationZ);
  //! Returns True if optional field UpperLimitActualTranslationZ is defined
  Standard_EXPORT bool HasUpperLimitActualTranslationZ() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_LowOrderKinematicPairWithRange,
                          StepKinematics_LowOrderKinematicPair)

private:
  double myLowerLimitActualRotationX;    //!< optional
  double myUpperLimitActualRotationX;    //!< optional
  double myLowerLimitActualRotationY;    //!< optional
  double myUpperLimitActualRotationY;    //!< optional
  double myLowerLimitActualRotationZ;    //!< optional
  double myUpperLimitActualRotationZ;    //!< optional
  double myLowerLimitActualTranslationX; //!< optional
  double myUpperLimitActualTranslationX; //!< optional
  double myLowerLimitActualTranslationY; //!< optional
  double myUpperLimitActualTranslationY; //!< optional
  double myLowerLimitActualTranslationZ; //!< optional
  double myUpperLimitActualTranslationZ; //!< optional
  bool   defLowerLimitActualRotationX;   //!< flag "is LowerLimitActualRotationX defined"
  bool   defUpperLimitActualRotationX;   //!< flag "is UpperLimitActualRotationX defined"
  bool   defLowerLimitActualRotationY;   //!< flag "is LowerLimitActualRotationY defined"
  bool   defUpperLimitActualRotationY;   //!< flag "is UpperLimitActualRotationY defined"
  bool   defLowerLimitActualRotationZ;   //!< flag "is LowerLimitActualRotationZ defined"
  bool   defUpperLimitActualRotationZ;   //!< flag "is UpperLimitActualRotationZ defined"
  // clang-format off
  bool defLowerLimitActualTranslationX; //!< flag "is LowerLimitActualTranslationX defined"
  bool defUpperLimitActualTranslationX; //!< flag "is UpperLimitActualTranslationX defined"
  bool defLowerLimitActualTranslationY; //!< flag "is LowerLimitActualTranslationY defined"
  bool defUpperLimitActualTranslationY; //!< flag "is UpperLimitActualTranslationY defined"
  bool defLowerLimitActualTranslationZ; //!< flag "is LowerLimitActualTranslationZ defined"
  bool defUpperLimitActualTranslationZ; //!< flag "is UpperLimitActualTranslationZ defined"
  // clang-format on
};
