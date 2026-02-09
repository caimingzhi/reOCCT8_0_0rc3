

#include "RWStepKinematics_RWGearPairWithRange.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_GearPairWithRange.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWGearPairWithRange::RWStepKinematics_RWGearPairWithRange() = default;

void RWStepKinematics_RWGearPairWithRange::ReadStep(
  const occ::handle<StepData_StepReaderData>&          theData,
  const int                                            theNum,
  occ::handle<Interface_Check>&                        theArch,
  const occ::handle<StepKinematics_GearPairWithRange>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 13, theArch, "gear_pair_with_range"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  occ::handle<TCollection_HAsciiString> aItemDefinedTransformation_Name;
  theData->ReadString(theNum,
                      2,
                      "item_defined_transformation.name",
                      theArch,
                      aItemDefinedTransformation_Name);

  occ::handle<TCollection_HAsciiString> aItemDefinedTransformation_Description;
  bool                                  hasItemDefinedTransformation_Description = true;
  if (theData->IsParamDefined(theNum, 3))
  {
    theData->ReadString(theNum,
                        3,
                        "item_defined_transformation.description",
                        theArch,
                        aItemDefinedTransformation_Description);
  }
  else
  {
    hasItemDefinedTransformation_Description = false;
    aItemDefinedTransformation_Description.Nullify();
  }

  occ::handle<StepRepr_RepresentationItem> aItemDefinedTransformation_TransformItem1;
  theData->ReadEntity(theNum,
                      4,
                      "item_defined_transformation.transform_item1",
                      theArch,
                      STANDARD_TYPE(StepRepr_RepresentationItem),
                      aItemDefinedTransformation_TransformItem1);

  occ::handle<StepRepr_RepresentationItem> aItemDefinedTransformation_TransformItem2;
  theData->ReadEntity(theNum,
                      5,
                      "item_defined_transformation.transform_item2",
                      theArch,
                      STANDARD_TYPE(StepRepr_RepresentationItem),
                      aItemDefinedTransformation_TransformItem2);

  occ::handle<StepKinematics_KinematicJoint> aKinematicPair_Joint;
  theData->ReadEntity(theNum,
                      6,
                      "kinematic_pair.joint",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicJoint),
                      aKinematicPair_Joint);

  double aGearPair_RadiusFirstLink;
  theData->ReadReal(theNum, 7, "gear_pair.radius_first_link", theArch, aGearPair_RadiusFirstLink);

  double aGearPair_RadiusSecondLink;
  theData->ReadReal(theNum, 8, "gear_pair.radius_second_link", theArch, aGearPair_RadiusSecondLink);

  double aGearPair_Bevel;
  theData->ReadReal(theNum, 9, "gear_pair.bevel", theArch, aGearPair_Bevel);

  double aGearPair_HelicalAngle;
  theData->ReadReal(theNum, 10, "gear_pair.helical_angle", theArch, aGearPair_HelicalAngle);

  double aGearPair_GearRatio;
  theData->ReadReal(theNum, 11, "gear_pair.gear_ratio", theArch, aGearPair_GearRatio);

  double aLowerLimitActualRotation1;
  bool   hasLowerLimitActualRotation1 = true;
  if (theData->IsParamDefined(theNum, 12))
  {
    theData->ReadReal(theNum,
                      12,
                      "lower_limit_actual_rotation1",
                      theArch,
                      aLowerLimitActualRotation1);
  }
  else
  {
    hasLowerLimitActualRotation1 = false;
    aLowerLimitActualRotation1   = 0;
  }

  double aUpperLimitActualRotation1;
  bool   hasUpperLimitActualRotation1 = true;
  if (theData->IsParamDefined(theNum, 13))
  {
    theData->ReadReal(theNum,
                      13,
                      "upper_limit_actual_rotation1",
                      theArch,
                      aUpperLimitActualRotation1);
  }
  else
  {
    hasUpperLimitActualRotation1 = false;
    aUpperLimitActualRotation1   = 0;
  }

  theEnt->Init(aRepresentationItem_Name,
               aItemDefinedTransformation_Name,
               hasItemDefinedTransformation_Description,
               aItemDefinedTransformation_Description,
               aItemDefinedTransformation_TransformItem1,
               aItemDefinedTransformation_TransformItem2,
               aKinematicPair_Joint,
               aGearPair_RadiusFirstLink,
               aGearPair_RadiusSecondLink,
               aGearPair_Bevel,
               aGearPair_HelicalAngle,
               aGearPair_GearRatio,
               hasLowerLimitActualRotation1,
               aLowerLimitActualRotation1,
               hasUpperLimitActualRotation1,
               aUpperLimitActualRotation1);
}

void RWStepKinematics_RWGearPairWithRange::WriteStep(
  StepData_StepWriter&                                 theSW,
  const occ::handle<StepKinematics_GearPairWithRange>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->ItemDefinedTransformation()->Name());

  if (theEnt->ItemDefinedTransformation()->HasDescription())
  {
    theSW.Send(theEnt->ItemDefinedTransformation()->Description());
  }
  else
    theSW.SendUndef();

  theSW.Send(theEnt->ItemDefinedTransformation()->TransformItem1());

  theSW.Send(theEnt->ItemDefinedTransformation()->TransformItem2());

  theSW.Send(theEnt->Joint());

  theSW.Send(theEnt->RadiusFirstLink());

  theSW.Send(theEnt->RadiusSecondLink());

  theSW.Send(theEnt->Bevel());

  theSW.Send(theEnt->HelicalAngle());

  theSW.Send(theEnt->GearRatio());

  if (theEnt->HasLowerLimitActualRotation1())
  {
    theSW.Send(theEnt->LowerLimitActualRotation1());
  }
  else
    theSW.SendUndef();

  if (theEnt->HasUpperLimitActualRotation1())
  {
    theSW.Send(theEnt->UpperLimitActualRotation1());
  }
  else
    theSW.SendUndef();
}

void RWStepKinematics_RWGearPairWithRange::Share(
  const occ::handle<StepKinematics_GearPairWithRange>& theEnt,
  Interface_EntityIterator&                            iter) const
{

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem1());

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem2());

  iter.AddItem(theEnt->StepKinematics_KinematicPair::Joint());
}
