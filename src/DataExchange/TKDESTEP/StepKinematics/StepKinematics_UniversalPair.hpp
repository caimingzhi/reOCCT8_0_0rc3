#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

//! Representation of STEP entity UniversalPair
class StepKinematics_UniversalPair : public StepKinematics_LowOrderKinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_UniversalPair();

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
    const bool                                        hasInputSkewAngle,
    const double                                      theInputSkewAngle);

  //! Returns field InputSkewAngle
  Standard_EXPORT double InputSkewAngle() const;
  //! Sets field InputSkewAngle
  Standard_EXPORT void SetInputSkewAngle(const double theInputSkewAngle);
  //! Returns True if optional field InputSkewAngle is defined
  Standard_EXPORT bool HasInputSkewAngle() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_UniversalPair, StepKinematics_LowOrderKinematicPair)

private:
  double myInputSkewAngle;  //!< optional
  bool   defInputSkewAngle; //!< flag "is InputSkewAngle defined"
};
