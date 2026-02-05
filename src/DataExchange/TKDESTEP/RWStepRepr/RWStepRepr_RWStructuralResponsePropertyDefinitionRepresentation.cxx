#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_StructuralResponsePropertyDefinitionRepresentation.hpp>

//=================================================================================================

RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation::
  RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation() = default;

//=================================================================================================

void RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                     data,
  const int                                                                       num,
  occ::handle<Interface_Check>&                                                   ach,
  const occ::handle<StepRepr_StructuralResponsePropertyDefinitionRepresentation>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "structural_response_property_definition_representation"))
    return;

  // Inherited fields of PropertyDefinitionRepresentation

  occ::handle<StepRepr_PropertyDefinition> aPropertyDefinitionRepresentation_Definition;
  data->ReadEntity(num,
                   1,
                   "property_definition_representation.definition",
                   ach,
                   STANDARD_TYPE(StepRepr_PropertyDefinition),
                   aPropertyDefinitionRepresentation_Definition);

  occ::handle<StepRepr_Representation> aPropertyDefinitionRepresentation_UsedRepresentation;
  data->ReadEntity(num,
                   2,
                   "property_definition_representation.used_representation",
                   ach,
                   STANDARD_TYPE(StepRepr_Representation),
                   aPropertyDefinitionRepresentation_UsedRepresentation);

  // skl 15.12.2002
  StepRepr_RepresentedDefinition aRepresentedDefinition;
  aRepresentedDefinition.SetValue(aPropertyDefinitionRepresentation_Definition);

  // Initialize entity
  ent->Init(/*aPropertyDefinitionRepresentation_Definition*/ aRepresentedDefinition,
            aPropertyDefinitionRepresentation_UsedRepresentation);
}

//=================================================================================================

void RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation::WriteStep(
  StepData_StepWriter&                                                            SW,
  const occ::handle<StepRepr_StructuralResponsePropertyDefinitionRepresentation>& ent) const
{

  // Inherited fields of PropertyDefinitionRepresentation

  SW.Send(ent->StepRepr_PropertyDefinitionRepresentation::Definition().Value());

  SW.Send(ent->StepRepr_PropertyDefinitionRepresentation::UsedRepresentation());
}

//=================================================================================================

void RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation::Share(
  const occ::handle<StepRepr_StructuralResponsePropertyDefinitionRepresentation>& ent,
  Interface_EntityIterator&                                                       iter) const
{

  // Inherited fields of PropertyDefinitionRepresentation

  iter.AddItem(ent->StepRepr_PropertyDefinitionRepresentation::Definition().Value());

  iter.AddItem(ent->StepRepr_PropertyDefinitionRepresentation::UsedRepresentation());
}
