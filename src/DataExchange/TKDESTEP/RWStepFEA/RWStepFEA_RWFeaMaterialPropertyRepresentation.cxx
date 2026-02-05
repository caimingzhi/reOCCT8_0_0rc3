#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaMaterialPropertyRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentation.hpp>
#include <StepRepr_DataEnvironment.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_Representation.hpp>

//=================================================================================================

RWStepFEA_RWFeaMaterialPropertyRepresentation::RWStepFEA_RWFeaMaterialPropertyRepresentation() =
  default;

//=================================================================================================

void RWStepFEA_RWFeaMaterialPropertyRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   data,
  const int                                                     num,
  occ::handle<Interface_Check>&                                 ach,
  const occ::handle<StepFEA_FeaMaterialPropertyRepresentation>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "fea_material_property_representation"))
    return;

  // Inherited fields of PropertyDefinitionRepresentation

  occ::handle<StepRepr_PropertyDefinition> aPropertyDefinitionRepresentation_Definition;
  data->ReadEntity(num,
                   1,
                   "property_definition_representation.definition",
                   ach,
                   STANDARD_TYPE(StepRepr_PropertyDefinition),
                   aPropertyDefinitionRepresentation_Definition);
  StepRepr_RepresentedDefinition aDefinition;
  aDefinition.SetValue(aPropertyDefinitionRepresentation_Definition);

  occ::handle<StepRepr_Representation> aPropertyDefinitionRepresentation_UsedRepresentation;
  data->ReadEntity(num,
                   2,
                   "property_definition_representation.used_representation",
                   ach,
                   STANDARD_TYPE(StepRepr_Representation),
                   aPropertyDefinitionRepresentation_UsedRepresentation);

  // Inherited fields of MaterialPropertyRepresentation

  occ::handle<StepRepr_DataEnvironment> aMaterialPropertyRepresentation_DependentEnvironment;
  data->ReadEntity(num,
                   3,
                   "material_property_representation.dependent_environment",
                   ach,
                   STANDARD_TYPE(StepRepr_DataEnvironment),
                   aMaterialPropertyRepresentation_DependentEnvironment);

  // Initialize entity
  ent->Init(aDefinition,
            aPropertyDefinitionRepresentation_UsedRepresentation,
            aMaterialPropertyRepresentation_DependentEnvironment);
}

//=================================================================================================

void RWStepFEA_RWFeaMaterialPropertyRepresentation::WriteStep(
  StepData_StepWriter&                                          SW,
  const occ::handle<StepFEA_FeaMaterialPropertyRepresentation>& ent) const
{

  // Inherited fields of PropertyDefinitionRepresentation

  SW.Send(ent->StepRepr_PropertyDefinitionRepresentation::Definition().PropertyDefinition());

  SW.Send(ent->StepRepr_PropertyDefinitionRepresentation::UsedRepresentation());

  // Inherited fields of MaterialPropertyRepresentation

  SW.Send(ent->StepRepr_MaterialPropertyRepresentation::DependentEnvironment());
}

//=================================================================================================

void RWStepFEA_RWFeaMaterialPropertyRepresentation::Share(
  const occ::handle<StepFEA_FeaMaterialPropertyRepresentation>& ent,
  Interface_EntityIterator&                                     iter) const
{

  // Inherited fields of PropertyDefinitionRepresentation

  iter.AddItem(ent->StepRepr_PropertyDefinitionRepresentation::Definition().PropertyDefinition());

  iter.AddItem(ent->StepRepr_PropertyDefinitionRepresentation::UsedRepresentation());

  // Inherited fields of MaterialPropertyRepresentation

  iter.AddItem(ent->StepRepr_MaterialPropertyRepresentation::DependentEnvironment());
}
