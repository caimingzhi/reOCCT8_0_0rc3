#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWPropertyDefinition.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_PropertyDefinition.hpp>

RWStepRepr_RWPropertyDefinition::RWStepRepr_RWPropertyDefinition() = default;

void RWStepRepr_RWPropertyDefinition::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepRepr_PropertyDefinition>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "property_definition"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  StepRepr_CharacterizedDefinition aDefinition;
  data->ReadEntity(num, 3, "definition", ach, aDefinition);

  ent->Init(aName, hasDescription, aDescription, aDefinition);
}

void RWStepRepr_RWPropertyDefinition::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepRepr_PropertyDefinition>& ent) const
{

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->Definition().Value());
}

void RWStepRepr_RWPropertyDefinition::Share(const occ::handle<StepRepr_PropertyDefinition>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.AddItem(ent->Definition().Value());
}
