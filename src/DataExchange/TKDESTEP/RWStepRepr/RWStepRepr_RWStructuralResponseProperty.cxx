#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWStructuralResponseProperty.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_StructuralResponseProperty.hpp>

RWStepRepr_RWStructuralResponseProperty::RWStepRepr_RWStructuralResponseProperty() = default;

void RWStepRepr_RWStructuralResponseProperty::ReadStep(
  const occ::handle<StepData_StepReaderData>&             data,
  const int                                               num,
  occ::handle<Interface_Check>&                           ach,
  const occ::handle<StepRepr_StructuralResponseProperty>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "structural_response_property"))
    return;

  occ::handle<TCollection_HAsciiString> aPropertyDefinition_Name;
  data->ReadString(num, 1, "property_definition.name", ach, aPropertyDefinition_Name);

  occ::handle<TCollection_HAsciiString> aPropertyDefinition_Description;
  data->ReadString(num, 2, "property_definition.description", ach, aPropertyDefinition_Description);

  StepRepr_CharacterizedDefinition aPropertyDefinition_Definition;
  data->ReadEntity(num, 3, "property_definition.definition", ach, aPropertyDefinition_Definition);

  ent->Init(aPropertyDefinition_Name,
            true,
            aPropertyDefinition_Description,
            aPropertyDefinition_Definition);
}

void RWStepRepr_RWStructuralResponseProperty::WriteStep(
  StepData_StepWriter&                                    SW,
  const occ::handle<StepRepr_StructuralResponseProperty>& ent) const
{

  SW.Send(ent->StepRepr_PropertyDefinition::Name());

  SW.Send(ent->StepRepr_PropertyDefinition::Description());

  SW.Send(ent->StepRepr_PropertyDefinition::Definition().Value());
}

void RWStepRepr_RWStructuralResponseProperty::Share(
  const occ::handle<StepRepr_StructuralResponseProperty>& ent,
  Interface_EntityIterator&                               iter) const
{

  iter.AddItem(ent->StepRepr_PropertyDefinition::Definition().Value());
}
