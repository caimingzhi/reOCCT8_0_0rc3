#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWMaterialProperty.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_MaterialProperty.hpp>

RWStepRepr_RWMaterialProperty::RWStepRepr_RWMaterialProperty() = default;

void RWStepRepr_RWMaterialProperty::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepRepr_MaterialProperty>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "material_property"))
    return;

  occ::handle<TCollection_HAsciiString> aPropertyDefinition_Name;
  data->ReadString(num, 1, "property_definition.name", ach, aPropertyDefinition_Name);

  occ::handle<TCollection_HAsciiString> aPropertyDefinition_Description;
  bool                                  hasPropertyDefinition_Description = true;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num,
                     2,
                     "property_definition.description",
                     ach,
                     aPropertyDefinition_Description);
  }
  else
  {
    hasPropertyDefinition_Description = false;
  }

  StepRepr_CharacterizedDefinition aPropertyDefinition_Definition;
  data->ReadEntity(num, 3, "property_definition.definition", ach, aPropertyDefinition_Definition);

  ent->Init(aPropertyDefinition_Name,
            hasPropertyDefinition_Description,
            aPropertyDefinition_Description,
            aPropertyDefinition_Definition);
}

void RWStepRepr_RWMaterialProperty::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepRepr_MaterialProperty>& ent) const
{

  SW.Send(ent->StepRepr_PropertyDefinition::Name());

  if (ent->StepRepr_PropertyDefinition::HasDescription())
  {
    SW.Send(ent->StepRepr_PropertyDefinition::Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->StepRepr_PropertyDefinition::Definition().Value());
}

void RWStepRepr_RWMaterialProperty::Share(const occ::handle<StepRepr_MaterialProperty>& ent,
                                          Interface_EntityIterator&                     iter) const
{

  iter.AddItem(ent->StepRepr_PropertyDefinition::Definition().Value());
}
