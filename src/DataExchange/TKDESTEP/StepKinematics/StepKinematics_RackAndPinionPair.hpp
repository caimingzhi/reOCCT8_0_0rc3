#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPairWithMotionCoupling.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

//! Representation of STEP entity RackAndPinionPair
class StepKinematics_RackAndPinionPair
    : public StepKinematics_LowOrderKinematicPairWithMotionCoupling
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_RackAndPinionPair();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const double                                      thePinionRadius);

  //! Returns field PinionRadius
  Standard_EXPORT double PinionRadius() const;
  //! Sets field PinionRadius
  Standard_EXPORT void SetPinionRadius(const double thePinionRadius);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RackAndPinionPair,
                          StepKinematics_LowOrderKinematicPairWithMotionCoupling)

private:
  double myPinionRadius;
};
