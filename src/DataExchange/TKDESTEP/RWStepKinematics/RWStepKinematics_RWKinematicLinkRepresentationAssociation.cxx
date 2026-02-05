// Created on : Sat May 02 12:41:15 2020

#include "RWStepKinematics_RWKinematicLinkRepresentationAssociation.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_KinematicLinkRepresentationAssociation.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationOrRepresentationReference.hpp>

//=================================================================================================

RWStepKinematics_RWKinematicLinkRepresentationAssociation::
  RWStepKinematics_RWKinematicLinkRepresentationAssociation() = default;

//=================================================================================================

void RWStepKinematics_RWKinematicLinkRepresentationAssociation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                               theData,
  const int                                                                 theNum,
  occ::handle<Interface_Check>&                                             theArch,
  const occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 4, theArch, "kinematic_link_representation_association"))
    return;

  // Inherited fields of RepresentationRelationship

  occ::handle<TCollection_HAsciiString> aRepresentationRelationship_Name;
  theData->ReadString(theNum,
                      1,
                      "representation_relationship.name",
                      theArch,
                      aRepresentationRelationship_Name);

  occ::handle<TCollection_HAsciiString> aRepresentationRelationship_Description;
  if (theData->IsParamDefined(theNum, 2))
  {
    theData->ReadString(theNum,
                        2,
                        "representation_relationship.description",
                        theArch,
                        aRepresentationRelationship_Description);
  }
  else
  {
    aRepresentationRelationship_Description.Nullify();
  }

  StepRepr_RepresentationOrRepresentationReference aRepresentationRelationship_Rep1;
  theData->ReadEntity(theNum,
                      3,
                      "representation_relationship.rep1",
                      theArch,
                      aRepresentationRelationship_Rep1);

  StepRepr_RepresentationOrRepresentationReference aRepresentationRelationship_Rep2;
  theData->ReadEntity(theNum,
                      4,
                      "representation_relationship.rep2",
                      theArch,
                      aRepresentationRelationship_Rep2);

  // Process only one type (Representation)
  if (aRepresentationRelationship_Rep1.CaseNumber() != 1
      || aRepresentationRelationship_Rep1.CaseNumber() != 1)
    return;

  // Initialize entity
  theEnt->Init(aRepresentationRelationship_Name,
               aRepresentationRelationship_Description,
               aRepresentationRelationship_Rep1.Representation(),
               aRepresentationRelationship_Rep2.Representation());
}

//=================================================================================================

void RWStepKinematics_RWKinematicLinkRepresentationAssociation::WriteStep(
  StepData_StepWriter&                                                      theSW,
  const occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>& theEnt) const
{

  // Own fields of RepresentationRelationship

  theSW.Send(theEnt->Name());

  if (theEnt->HasDescription())
  {
    theSW.Send(theEnt->Description());
  }
  else
    theSW.SendUndef();

  theSW.Send(theEnt->Rep1());

  theSW.Send(theEnt->Rep2());
}

//=================================================================================================

void RWStepKinematics_RWKinematicLinkRepresentationAssociation::Share(
  const occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>& theEnt,
  Interface_EntityIterator&                                                 iter) const
{

  // Inherited fields of RepresentationRelationship

  iter.AddItem(theEnt->StepRepr_RepresentationRelationship::Rep1());

  iter.AddItem(theEnt->StepRepr_RepresentationRelationship::Rep2());
}
