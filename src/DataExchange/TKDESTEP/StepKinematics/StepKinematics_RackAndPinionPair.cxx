// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_RackAndPinionPair.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_RackAndPinionPair,
                           StepKinematics_LowOrderKinematicPairWithMotionCoupling)

//=================================================================================================

StepKinematics_RackAndPinionPair::StepKinematics_RackAndPinionPair() = default;

//=================================================================================================

void StepKinematics_RackAndPinionPair::Init(
  const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
  const bool                                        hasItemDefinedTransformation_Description,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
  const double                                      thePinionRadius)
{
  StepKinematics_LowOrderKinematicPairWithMotionCoupling::Init(
    theRepresentationItem_Name,
    theItemDefinedTransformation_Name,
    hasItemDefinedTransformation_Description,
    theItemDefinedTransformation_Description,
    theItemDefinedTransformation_TransformItem1,
    theItemDefinedTransformation_TransformItem2,
    theKinematicPair_Joint);

  myPinionRadius = thePinionRadius;
}

//=================================================================================================

double StepKinematics_RackAndPinionPair::PinionRadius() const
{
  return myPinionRadius;
}

//=================================================================================================

void StepKinematics_RackAndPinionPair::SetPinionRadius(const double thePinionRadius)
{
  myPinionRadius = thePinionRadius;
}
