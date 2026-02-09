#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWIdentificationRole.hpp"
#include <StepBasic_IdentificationRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWIdentificationRole::RWStepBasic_RWIdentificationRole() = default;

void RWStepBasic_RWIdentificationRole::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepBasic_IdentificationRole>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "identification_role"))
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

void RWStepBasic_RWIdentificationRole::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepBasic_IdentificationRole>& ent) const
{

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();
}

void RWStepBasic_RWIdentificationRole::Share(const occ::handle<StepBasic_IdentificationRole>&,
                                             Interface_EntityIterator&) const
{
}
