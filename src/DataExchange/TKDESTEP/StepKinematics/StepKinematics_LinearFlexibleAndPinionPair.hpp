#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPairWithMotionCoupling.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_LinearFlexibleAndPinionPair
    : public StepKinematics_LowOrderKinematicPairWithMotionCoupling
{
public:
  Standard_EXPORT StepKinematics_LinearFlexibleAndPinionPair();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const double                                      thePinionRadius);

  Standard_EXPORT double PinionRadius() const;

  Standard_EXPORT void SetPinionRadius(const double thePinionRadius);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_LinearFlexibleAndPinionPair,
                          StepKinematics_LowOrderKinematicPairWithMotionCoupling)

private:
  double myPinionRadius;
};
