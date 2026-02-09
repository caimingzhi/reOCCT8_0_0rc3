

#include "RWStepKinematics_RWLowOrderKinematicPair.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

RWStepKinematics_RWLowOrderKinematicPair::RWStepKinematics_RWLowOrderKinematicPair() = default;

void RWStepKinematics_RWLowOrderKinematicPair::ReadStep(
  const occ::handle<StepData_StepReaderData>&              theData,
  const int                                                theNum,
  occ::handle<Interface_Check>&                            theArch,
  const occ::handle<StepKinematics_LowOrderKinematicPair>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 12, theArch, "low_order_kinematic_pair"))
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

  bool aTX;
  theData->ReadBoolean(theNum, 7, "t_x", theArch, aTX);

  bool aTY;
  theData->ReadBoolean(theNum, 8, "t_y", theArch, aTY);

  bool aTZ;
  theData->ReadBoolean(theNum, 9, "t_z", theArch, aTZ);

  bool aRX;
  theData->ReadBoolean(theNum, 10, "r_x", theArch, aRX);

  bool aRY;
  theData->ReadBoolean(theNum, 11, "r_y", theArch, aRY);

  bool aRZ;
  theData->ReadBoolean(theNum, 12, "r_z", theArch, aRZ);

  theEnt->Init(aRepresentationItem_Name,
               aItemDefinedTransformation_Name,
               hasItemDefinedTransformation_Description,
               aItemDefinedTransformation_Description,
               aItemDefinedTransformation_TransformItem1,
               aItemDefinedTransformation_TransformItem2,
               aKinematicPair_Joint,
               aTX,
               aTY,
               aTZ,
               aRX,
               aRY,
               aRZ);
}

void RWStepKinematics_RWLowOrderKinematicPair::WriteStep(
  StepData_StepWriter&                                     theSW,
  const occ::handle<StepKinematics_LowOrderKinematicPair>& theEnt) const
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

  theSW.SendBoolean(theEnt->TX());

  theSW.SendBoolean(theEnt->TY());

  theSW.SendBoolean(theEnt->TZ());

  theSW.SendBoolean(theEnt->RX());

  theSW.SendBoolean(theEnt->RY());

  theSW.SendBoolean(theEnt->RZ());
}

void RWStepKinematics_RWLowOrderKinematicPair::Share(
  const occ::handle<StepKinematics_LowOrderKinematicPair>& theEnt,
  Interface_EntityIterator&                                iter) const
{

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem1());

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem2());

  iter.AddItem(theEnt->StepKinematics_KinematicPair::Joint());
}
