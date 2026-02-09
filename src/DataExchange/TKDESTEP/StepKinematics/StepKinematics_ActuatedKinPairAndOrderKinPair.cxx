#include <StepKinematics_ActuatedKinPairAndOrderKinPair.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepKinematics_ActuatedKinematicPair.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_ActuatedKinPairAndOrderKinPair,
                           StepKinematics_KinematicPair)

StepKinematics_ActuatedKinPairAndOrderKinPair::StepKinematics_ActuatedKinPairAndOrderKinPair() =
  default;

void StepKinematics_ActuatedKinPairAndOrderKinPair::Init(
  const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
  const bool                                        hasItemDefinedTransformation_Description,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theJoint,
  const occ::handle<StepKinematics_ActuatedKinematicPair>& theActuatedKinematicPair,
  const occ::handle<StepKinematics_KinematicPair>&         theOrderKinematicPair)
{
  StepKinematics_KinematicPair::Init(theRepresentationItem_Name,
                                     theItemDefinedTransformation_Name,
                                     hasItemDefinedTransformation_Description,
                                     theItemDefinedTransformation_Description,
                                     theItemDefinedTransformation_TransformItem1,
                                     theItemDefinedTransformation_TransformItem2,
                                     theJoint);
  SetActuatedKinematicPair(theActuatedKinematicPair);
  SetOrderKinematicPair(theOrderKinematicPair);
}
