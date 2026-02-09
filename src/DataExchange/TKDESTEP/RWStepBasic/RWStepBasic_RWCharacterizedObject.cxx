#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWCharacterizedObject.hpp"
#include <StepBasic_CharacterizedObject.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWCharacterizedObject::RWStepBasic_RWCharacterizedObject() = default;

void RWStepBasic_RWCharacterizedObject::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepBasic_CharacterizedObject>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "characterized_object"))
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

  ent->Init(aName, hasDescription, aDescription);
}

void RWStepBasic_RWCharacterizedObject::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepBasic_CharacterizedObject>& ent) const
{

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();
}

void RWStepBasic_RWCharacterizedObject::Share(const occ::handle<StepBasic_CharacterizedObject>&,
                                              Interface_EntityIterator&) const
{
}
