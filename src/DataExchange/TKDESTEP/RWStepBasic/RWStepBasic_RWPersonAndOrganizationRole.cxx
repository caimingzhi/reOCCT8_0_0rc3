

#include "RWStepBasic_RWPersonAndOrganizationRole.hpp"
#include <StepBasic_PersonAndOrganizationRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWPersonAndOrganizationRole::RWStepBasic_RWPersonAndOrganizationRole() = default;

void RWStepBasic_RWPersonAndOrganizationRole::ReadStep(
  const occ::handle<StepData_StepReaderData>&             data,
  const int                                               num,
  occ::handle<Interface_Check>&                           ach,
  const occ::handle<StepBasic_PersonAndOrganizationRole>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "person_and_organization_role"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepBasic_RWPersonAndOrganizationRole::WriteStep(
  StepData_StepWriter&                                    SW,
  const occ::handle<StepBasic_PersonAndOrganizationRole>& ent) const
{

  SW.Send(ent->Name());
}
