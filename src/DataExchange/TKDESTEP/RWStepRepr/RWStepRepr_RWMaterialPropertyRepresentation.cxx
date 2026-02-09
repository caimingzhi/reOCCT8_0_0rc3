#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWMaterialPropertyRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_DataEnvironment.hpp>
#include <StepRepr_MaterialPropertyRepresentation.hpp>
#include <StepRepr_Representation.hpp>

RWStepRepr_RWMaterialPropertyRepresentation::RWStepRepr_RWMaterialPropertyRepresentation() =
  default;

void RWStepRepr_RWMaterialPropertyRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepRepr_MaterialPropertyRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "material_property_representation"))
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

  occ::handle<StepRepr_DataEnvironment> aDependentEnvironment;
  data->ReadEntity(num,
                   3,
                   "dependent_environment",
                   ach,
                   STANDARD_TYPE(StepRepr_DataEnvironment),
                   aDependentEnvironment);

  ent->Init(aPropertyDefinitionRepresentation_Definition,
            aPropertyDefinitionRepresentation_UsedRepresentation,
            aDependentEnvironment);
}

void RWStepRepr_RWMaterialPropertyRepresentation::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepRepr_MaterialPropertyRepresentation>& ent) const
{

  SW.Send(ent->StepRepr_PropertyDefinitionRepresentation::Definition().Value());

  SW.Send(ent->StepRepr_PropertyDefinitionRepresentation::UsedRepresentation());

  SW.Send(ent->DependentEnvironment());
}

void RWStepRepr_RWMaterialPropertyRepresentation::Share(
  const occ::handle<StepRepr_MaterialPropertyRepresentation>& ent,
  Interface_EntityIterator&                                   iter) const
{

  iter.AddItem(ent->StepRepr_PropertyDefinitionRepresentation::Definition().Value());

  iter.AddItem(ent->StepRepr_PropertyDefinitionRepresentation::UsedRepresentation());

  iter.AddItem(ent->DependentEnvironment());
}
