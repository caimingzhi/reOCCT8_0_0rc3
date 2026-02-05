// Created on : Sat May 02 12:41:16 2020

#include "RWStepKinematics_RWScrewPairWithRange.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_ScrewPairWithRange.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <Standard_Real.hpp>

//=================================================================================================

RWStepKinematics_RWScrewPairWithRange::RWStepKinematics_RWScrewPairWithRange() = default;

//=================================================================================================

void RWStepKinematics_RWScrewPairWithRange::ReadStep(
  const occ::handle<StepData_StepReaderData>&           theData,
  const int                                             theNum,
  occ::handle<Interface_Check>&                         theArch,
  const occ::handle<StepKinematics_ScrewPairWithRange>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 9, theArch, "screw_pair_with_range"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  // Inherited fields of ItemDefinedTransformation

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

  // Inherited fields of KinematicPair

  occ::handle<StepKinematics_KinematicJoint> aKinematicPair_Joint;
  theData->ReadEntity(theNum,
                      6,
                      "kinematic_pair.joint",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicJoint),
                      aKinematicPair_Joint);

  // Inherited fields of ScrewPair

  double aScrewPair_Pitch;
  theData->ReadReal(theNum, 7, "screw_pair.pitch", theArch, aScrewPair_Pitch);

  // Own fields of ScrewPairWithRange

  double aLowerLimitActualRotation;
  bool   hasLowerLimitActualRotation = true;
  if (theData->IsParamDefined(theNum, 8))
  {
    theData->ReadReal(theNum, 8, "lower_limit_actual_rotation", theArch, aLowerLimitActualRotation);
  }
  else
  {
    hasLowerLimitActualRotation = false;
    aLowerLimitActualRotation   = 0;
  }

  double aUpperLimitActualRotation;
  bool   hasUpperLimitActualRotation = true;
  if (theData->IsParamDefined(theNum, 9))
  {
    theData->ReadReal(theNum, 9, "upper_limit_actual_rotation", theArch, aUpperLimitActualRotation);
  }
  else
  {
    hasUpperLimitActualRotation = false;
    aUpperLimitActualRotation   = 0;
  }

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name,
               aItemDefinedTransformation_Name,
               hasItemDefinedTransformation_Description,
               aItemDefinedTransformation_Description,
               aItemDefinedTransformation_TransformItem1,
               aItemDefinedTransformation_TransformItem2,
               aKinematicPair_Joint,
               aScrewPair_Pitch,
               hasLowerLimitActualRotation,
               aLowerLimitActualRotation,
               hasUpperLimitActualRotation,
               aUpperLimitActualRotation);
}

//=================================================================================================

void RWStepKinematics_RWScrewPairWithRange::WriteStep(
  StepData_StepWriter&                                  theSW,
  const occ::handle<StepKinematics_ScrewPairWithRange>& theEnt) const
{

  // Own fields of RepresentationItem

  theSW.Send(theEnt->Name());

  // Inherited fields of ItemDefinedTransformation

  theSW.Send(theEnt->ItemDefinedTransformation()->Name());

  if (theEnt->ItemDefinedTransformation()->HasDescription())
  {
    theSW.Send(theEnt->ItemDefinedTransformation()->Description());
  }
  else
    theSW.SendUndef();

  theSW.Send(theEnt->ItemDefinedTransformation()->TransformItem1());

  theSW.Send(theEnt->ItemDefinedTransformation()->TransformItem2());

  // Own fields of KinematicPair

  theSW.Send(theEnt->Joint());

  // Own fields of ScrewPair

  theSW.Send(theEnt->Pitch());

  // Own fields of ScrewPairWithRange

  if (theEnt->HasLowerLimitActualRotation())
  {
    theSW.Send(theEnt->LowerLimitActualRotation());
  }
  else
    theSW.SendUndef();

  if (theEnt->HasUpperLimitActualRotation())
  {
    theSW.Send(theEnt->UpperLimitActualRotation());
  }
  else
    theSW.SendUndef();
}

//=================================================================================================

void RWStepKinematics_RWScrewPairWithRange::Share(
  const occ::handle<StepKinematics_ScrewPairWithRange>& theEnt,
  Interface_EntityIterator&                             iter) const
{

  // Inherited fields of RepresentationItem

  // Inherited fields of ItemDefinedTransformation

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem1());

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem2());

  // Inherited fields of KinematicPair

  iter.AddItem(theEnt->StepKinematics_KinematicPair::Joint());

  // Inherited fields of ScrewPair

  // Own fields of ScrewPairWithRange
}
