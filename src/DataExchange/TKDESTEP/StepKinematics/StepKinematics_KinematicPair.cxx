

#include <StepKinematics_KinematicPair.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_KinematicPair, StepGeom_GeometricRepresentationItem)

StepKinematics_KinematicPair::StepKinematics_KinematicPair() = default;

void StepKinematics_KinematicPair::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>& theItemDefinedTransformation_Name,
  const bool,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theJoint)
{
  StepGeom_GeometricRepresentationItem::Init(theRepresentationItem_Name);
  myItemDefinedTransformation = new StepRepr_ItemDefinedTransformation;
  myItemDefinedTransformation->Init(theItemDefinedTransformation_Name,

                                    theItemDefinedTransformation_Description,
                                    theItemDefinedTransformation_TransformItem1,
                                    theItemDefinedTransformation_TransformItem2);

  myJoint = theJoint;
}

occ::handle<StepRepr_ItemDefinedTransformation> StepKinematics_KinematicPair::
  ItemDefinedTransformation() const
{
  return myItemDefinedTransformation;
}

void StepKinematics_KinematicPair::SetItemDefinedTransformation(
  const occ::handle<StepRepr_ItemDefinedTransformation>& theItemDefinedTransformation)
{
  myItemDefinedTransformation = theItemDefinedTransformation;
}

occ::handle<StepKinematics_KinematicJoint> StepKinematics_KinematicPair::Joint() const
{
  return myJoint;
}

void StepKinematics_KinematicPair::SetJoint(
  const occ::handle<StepKinematics_KinematicJoint>& theJoint)
{
  myJoint = theJoint;
}
