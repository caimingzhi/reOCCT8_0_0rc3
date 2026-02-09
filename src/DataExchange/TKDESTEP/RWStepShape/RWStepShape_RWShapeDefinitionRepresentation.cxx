#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWShapeDefinitionRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_Representation.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>

RWStepShape_RWShapeDefinitionRepresentation::RWStepShape_RWShapeDefinitionRepresentation() =
  default;

void RWStepShape_RWShapeDefinitionRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepShape_ShapeDefinitionRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "shape_definition_representation"))
    return;

  StepRepr_RepresentedDefinition aPropertyDefinitionRepresentation_Definition;
  data->ReadEntity(num,
                   1,
                   "property_definition_representation.definition",
                   ach,
                   aPropertyDefinitionRepresentation_Definition);

  occ::handle<StepRepr_Representation> aPropertyDefinitionRepresentation_UsedRepresentation;
  data->ReadEntity(num,
                   2,
                   "property_definition_representation.used_representation",
                   ach,
                   STANDARD_TYPE(StepRepr_Representation),
                   aPropertyDefinitionRepresentation_UsedRepresentation);

  ent->Init(aPropertyDefinitionRepresentation_Definition,
            aPropertyDefinitionRepresentation_UsedRepresentation);
}

void RWStepShape_RWShapeDefinitionRepresentation::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepShape_ShapeDefinitionRepresentation>& ent) const
{

  SW.Send(ent->StepRepr_PropertyDefinitionRepresentation::Definition().Value());

  SW.Send(ent->StepRepr_PropertyDefinitionRepresentation::UsedRepresentation());
}

void RWStepShape_RWShapeDefinitionRepresentation::Share(
  const occ::handle<StepShape_ShapeDefinitionRepresentation>& ent,
  Interface_EntityIterator&                                   iter) const
{

  iter.AddItem(ent->StepRepr_PropertyDefinitionRepresentation::Definition().Value());

  iter.AddItem(ent->StepRepr_PropertyDefinitionRepresentation::UsedRepresentation());
}
