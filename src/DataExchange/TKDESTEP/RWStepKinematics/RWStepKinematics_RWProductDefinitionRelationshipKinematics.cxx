// Created on : Sat May 02 12:41:15 2020

#include "RWStepKinematics_RWProductDefinitionRelationshipKinematics.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_ProductDefinitionRelationshipKinematics.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_CharacterizedDefinition.hpp>

//=================================================================================================

RWStepKinematics_RWProductDefinitionRelationshipKinematics::
  RWStepKinematics_RWProductDefinitionRelationshipKinematics() = default;

//=================================================================================================

void RWStepKinematics_RWProductDefinitionRelationshipKinematics::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                theData,
  const int                                                                  theNum,
  occ::handle<Interface_Check>&                                              theArch,
  const occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 3, theArch, "product_definition_relationship_kinematics"))
    return;

  // Inherited fields of PropertyDefinition

  occ::handle<TCollection_HAsciiString> aPropertyDefinition_Name;
  theData->ReadString(theNum, 1, "property_definition.name", theArch, aPropertyDefinition_Name);

  occ::handle<TCollection_HAsciiString> aPropertyDefinition_Description;
  bool                                  hasPropertyDefinition_Description = true;
  if (theData->IsParamDefined(theNum, 2))
  {
    theData->ReadString(theNum,
                        2,
                        "property_definition.description",
                        theArch,
                        aPropertyDefinition_Description);
  }
  else
  {
    hasPropertyDefinition_Description = false;
    aPropertyDefinition_Description.Nullify();
  }

  StepRepr_CharacterizedDefinition aPropertyDefinition_Definition;
  theData->ReadEntity(theNum,
                      3,
                      "property_definition.definition",
                      theArch,
                      aPropertyDefinition_Definition);

  // Initialize entity
  theEnt->Init(aPropertyDefinition_Name,
               hasPropertyDefinition_Description,
               aPropertyDefinition_Description,
               aPropertyDefinition_Definition);
}

//=================================================================================================

void RWStepKinematics_RWProductDefinitionRelationshipKinematics::WriteStep(
  StepData_StepWriter&                                                       theSW,
  const occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>& theEnt) const
{

  // Own fields of PropertyDefinition

  theSW.Send(theEnt->Name());

  if (theEnt->HasDescription())
  {
    theSW.Send(theEnt->Description());
  }
  else
    theSW.SendUndef();

  theSW.Send(theEnt->Definition().Value());
}

//=================================================================================================

void RWStepKinematics_RWProductDefinitionRelationshipKinematics::Share(
  const occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>& theEnt,
  Interface_EntityIterator&                                                  iter) const
{

  // Inherited fields of PropertyDefinition

  iter.AddItem(theEnt->StepRepr_PropertyDefinition::Definition().Value());
}
