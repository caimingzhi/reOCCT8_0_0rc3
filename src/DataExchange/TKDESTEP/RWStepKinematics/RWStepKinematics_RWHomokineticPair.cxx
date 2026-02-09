

#include "RWStepKinematics_RWHomokineticPair.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_HomokineticPair.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWHomokineticPair::RWStepKinematics_RWHomokineticPair() = default;

void RWStepKinematics_RWHomokineticPair::ReadStep(
  const occ::handle<StepData_StepReaderData>&        theData,
  const int                                          theNum,
  occ::handle<Interface_Check>&                      theArch,
  const occ::handle<StepKinematics_HomokineticPair>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 13, theArch, "homokinetic_pair"))
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

  bool aLowOrderKinematicPair_TX;
  theData->ReadBoolean(theNum,
                       7,
                       "low_order_kinematic_pair.t_x",
                       theArch,
                       aLowOrderKinematicPair_TX);

  bool aLowOrderKinematicPair_TY;
  theData->ReadBoolean(theNum,
                       8,
                       "low_order_kinematic_pair.t_y",
                       theArch,
                       aLowOrderKinematicPair_TY);

  bool aLowOrderKinematicPair_TZ;
  theData->ReadBoolean(theNum,
                       9,
                       "low_order_kinematic_pair.t_z",
                       theArch,
                       aLowOrderKinematicPair_TZ);

  bool aLowOrderKinematicPair_RX;
  theData->ReadBoolean(theNum,
                       10,
                       "low_order_kinematic_pair.r_x",
                       theArch,
                       aLowOrderKinematicPair_RX);

  bool aLowOrderKinematicPair_RY;
  theData->ReadBoolean(theNum,
                       11,
                       "low_order_kinematic_pair.r_y",
                       theArch,
                       aLowOrderKinematicPair_RY);

  bool aLowOrderKinematicPair_RZ;
  theData->ReadBoolean(theNum,
                       12,
                       "low_order_kinematic_pair.r_z",
                       theArch,
                       aLowOrderKinematicPair_RZ);

  double aUniversalPair_InputSkewAngle;
  bool   hasUniversalPair_InputSkewAngle = true;
  if (theData->IsParamDefined(theNum, 13))
  {
    theData->ReadReal(theNum,
                      13,
                      "universal_pair.input_skew_angle",
                      theArch,
                      aUniversalPair_InputSkewAngle);
  }
  else
  {
    hasUniversalPair_InputSkewAngle = false;
    aUniversalPair_InputSkewAngle   = 0;
  }

  theEnt->Init(aRepresentationItem_Name,
               aItemDefinedTransformation_Name,
               hasItemDefinedTransformation_Description,
               aItemDefinedTransformation_Description,
               aItemDefinedTransformation_TransformItem1,
               aItemDefinedTransformation_TransformItem2,
               aKinematicPair_Joint,
               aLowOrderKinematicPair_TX,
               aLowOrderKinematicPair_TY,
               aLowOrderKinematicPair_TZ,
               aLowOrderKinematicPair_RX,
               aLowOrderKinematicPair_RY,
               aLowOrderKinematicPair_RZ,
               hasUniversalPair_InputSkewAngle,
               aUniversalPair_InputSkewAngle);
}

void RWStepKinematics_RWHomokineticPair::WriteStep(
  StepData_StepWriter&                               theSW,
  const occ::handle<StepKinematics_HomokineticPair>& theEnt) const
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

  if (theEnt->HasInputSkewAngle())
  {
    theSW.Send(theEnt->InputSkewAngle());
  }
  else
    theSW.SendUndef();
}

void RWStepKinematics_RWHomokineticPair::Share(
  const occ::handle<StepKinematics_HomokineticPair>& theEnt,
  Interface_EntityIterator&                          iter) const
{

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem1());

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem2());

  iter.AddItem(theEnt->StepKinematics_KinematicPair::Joint());
}
