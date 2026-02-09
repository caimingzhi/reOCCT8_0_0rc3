

#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWMaterialDesignation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_MaterialDesignation.hpp>

RWStepRepr_RWMaterialDesignation::RWStepRepr_RWMaterialDesignation() = default;

void RWStepRepr_RWMaterialDesignation::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepRepr_MaterialDesignation>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "material_designation"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  StepRepr_CharacterizedDefinition aOfDefinition;

  data->ReadEntity(num, 2, "of_definition", ach, aOfDefinition);

  ent->Init(aName, aOfDefinition);
}

void RWStepRepr_RWMaterialDesignation::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepRepr_MaterialDesignation>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->OfDefinition().Value());
}

void RWStepRepr_RWMaterialDesignation::Share(const occ::handle<StepRepr_MaterialDesignation>& ent,
                                             Interface_EntityIterator& iter) const
{
  iter.AddItem(ent->OfDefinition().Value());
}
