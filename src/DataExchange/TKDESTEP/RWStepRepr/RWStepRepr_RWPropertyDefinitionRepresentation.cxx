#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWPropertyDefinitionRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_PropertyDefinitionRepresentation.hpp>
#include <StepRepr_Representation.hpp>

RWStepRepr_RWPropertyDefinitionRepresentation::RWStepRepr_RWPropertyDefinitionRepresentation() =
  default;

void RWStepRepr_RWPropertyDefinitionRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   data,
  const int                                                     num,
  occ::handle<Interface_Check>&                                 ach,
  const occ::handle<StepRepr_PropertyDefinitionRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "property_definition_representation"))
    return;

  StepRepr_RepresentedDefinition aDefinition;
  data->ReadEntity(num, 1, "definition", ach, aDefinition);

  occ::handle<StepRepr_Representation> aUsedRepresentation;
  data->ReadEntity(num,
                   2,
                   "used_representation",
                   ach,
                   STANDARD_TYPE(StepRepr_Representation),
                   aUsedRepresentation);

  ent->Init(aDefinition, aUsedRepresentation);
}

void RWStepRepr_RWPropertyDefinitionRepresentation::WriteStep(
  StepData_StepWriter&                                          SW,
  const occ::handle<StepRepr_PropertyDefinitionRepresentation>& ent) const
{

  SW.Send(ent->Definition().Value());

  SW.Send(ent->UsedRepresentation());
}

void RWStepRepr_RWPropertyDefinitionRepresentation::Share(
  const occ::handle<StepRepr_PropertyDefinitionRepresentation>& ent,
  Interface_EntityIterator&                                     iter) const
{

  iter.AddItem(ent->Definition().Value());

  iter.AddItem(ent->UsedRepresentation());
}
