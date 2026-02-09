

#include "RWStepBasic_RWOrganizationRole.hpp"
#include <StepBasic_OrganizationRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWOrganizationRole::RWStepBasic_RWOrganizationRole() = default;

void RWStepBasic_RWOrganizationRole::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepBasic_OrganizationRole>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "organization_role"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepBasic_RWOrganizationRole::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepBasic_OrganizationRole>& ent) const
{

  SW.Send(ent->Name());
}
