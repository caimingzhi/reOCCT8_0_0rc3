

#include "RWStepKinematics_RWSphericalPairWithPinAndRange.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_SphericalPairWithPinAndRange.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWSphericalPairWithPinAndRange::RWStepKinematics_RWSphericalPairWithPinAndRange() =
  default;

void RWStepKinematics_RWSphericalPairWithPinAndRange::ReadStep(
  const occ::handle<StepData_StepReaderData>&                     theData,
  const int                                                       theNum,
  occ::handle<Interface_Check>&                                   theArch,
  const occ::handle<StepKinematics_SphericalPairWithPinAndRange>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 16, theArch, "spherical_pair_with_pin_and_range"))
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

  double aLowerLimitYaw;
  bool   hasLowerLimitYaw = true;
  if (theData->IsParamDefined(theNum, 13))
  {
    theData->ReadReal(theNum, 13, "lower_limit_yaw", theArch, aLowerLimitYaw);
  }
  else
  {
    hasLowerLimitYaw = false;
    aLowerLimitYaw   = 0;
  }

  double aUpperLimitYaw;
  bool   hasUpperLimitYaw = true;
  if (theData->IsParamDefined(theNum, 14))
  {
    theData->ReadReal(theNum, 14, "upper_limit_yaw", theArch, aUpperLimitYaw);
  }
  else
  {
    hasUpperLimitYaw = false;
    aUpperLimitYaw   = 0;
  }

  double aLowerLimitRoll;
  bool   hasLowerLimitRoll = true;
  if (theData->IsParamDefined(theNum, 15))
  {
    theData->ReadReal(theNum, 15, "lower_limit_roll", theArch, aLowerLimitRoll);
  }
  else
  {
    hasLowerLimitRoll = false;
    aLowerLimitRoll   = 0;
  }

  double aUpperLimitRoll;
  bool   hasUpperLimitRoll = true;
  if (theData->IsParamDefined(theNum, 16))
  {
    theData->ReadReal(theNum, 16, "upper_limit_roll", theArch, aUpperLimitRoll);
  }
  else
  {
    hasUpperLimitRoll = false;
    aUpperLimitRoll   = 0;
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
               hasLowerLimitYaw,
               aLowerLimitYaw,
               hasUpperLimitYaw,
               aUpperLimitYaw,
               hasLowerLimitRoll,
               aLowerLimitRoll,
               hasUpperLimitRoll,
               aUpperLimitRoll);
}

void RWStepKinematics_RWSphericalPairWithPinAndRange::WriteStep(
  StepData_StepWriter&                                            theSW,
  const occ::handle<StepKinematics_SphericalPairWithPinAndRange>& theEnt) const
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

  if (theEnt->HasLowerLimitYaw())
  {
    theSW.Send(theEnt->LowerLimitYaw());
  }
  else
    theSW.SendUndef();

  if (theEnt->HasUpperLimitYaw())
  {
    theSW.Send(theEnt->UpperLimitYaw());
  }
  else
    theSW.SendUndef();

  if (theEnt->HasLowerLimitRoll())
  {
    theSW.Send(theEnt->LowerLimitRoll());
  }
  else
    theSW.SendUndef();

  if (theEnt->HasUpperLimitRoll())
  {
    theSW.Send(theEnt->UpperLimitRoll());
  }
  else
    theSW.SendUndef();
}

void RWStepKinematics_RWSphericalPairWithPinAndRange::Share(
  const occ::handle<StepKinematics_SphericalPairWithPinAndRange>& theEnt,
  Interface_EntityIterator&                                       iter) const
{

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem1());

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem2());

  iter.AddItem(theEnt->StepKinematics_KinematicPair::Joint());
}
