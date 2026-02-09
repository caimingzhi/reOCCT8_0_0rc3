#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWRoleAssociation.hpp"
#include <StepBasic_ObjectRole.hpp>
#include <StepBasic_RoleAssociation.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWRoleAssociation::RWStepBasic_RWRoleAssociation() = default;

void RWStepBasic_RWRoleAssociation::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepBasic_RoleAssociation>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "role_association"))
    return;

  occ::handle<StepBasic_ObjectRole> aRole;
  data->ReadEntity(num, 1, "role", ach, STANDARD_TYPE(StepBasic_ObjectRole), aRole);

  StepBasic_RoleSelect aItemWithRole;
  data->ReadEntity(num, 2, "item_with_role", ach, aItemWithRole);

  ent->Init(aRole, aItemWithRole);
}

void RWStepBasic_RWRoleAssociation::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepBasic_RoleAssociation>& ent) const
{

  SW.Send(ent->Role());

  SW.Send(ent->ItemWithRole().Value());
}

void RWStepBasic_RWRoleAssociation::Share(const occ::handle<StepBasic_RoleAssociation>& ent,
                                          Interface_EntityIterator&                     iter) const
{

  iter.AddItem(ent->Role());

  iter.AddItem(ent->ItemWithRole().Value());
}
