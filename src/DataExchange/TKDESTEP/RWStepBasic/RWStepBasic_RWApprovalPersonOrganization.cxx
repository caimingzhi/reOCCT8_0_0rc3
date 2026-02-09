

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWApprovalPersonOrganization.hpp"
#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalPersonOrganization.hpp>
#include <StepBasic_ApprovalRole.hpp>
#include <StepBasic_PersonOrganizationSelect.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWApprovalPersonOrganization::RWStepBasic_RWApprovalPersonOrganization() = default;

void RWStepBasic_RWApprovalPersonOrganization::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepBasic_ApprovalPersonOrganization>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "approval_person_organization"))
    return;

  StepBasic_PersonOrganizationSelect aPersonOrganization;

  data->ReadEntity(num, 1, "person_organization", ach, aPersonOrganization);

  occ::handle<StepBasic_Approval> aAuthorizedApproval;

  data->ReadEntity(num,
                   2,
                   "authorized_approval",
                   ach,
                   STANDARD_TYPE(StepBasic_Approval),
                   aAuthorizedApproval);

  occ::handle<StepBasic_ApprovalRole> aRole;

  data->ReadEntity(num, 3, "role", ach, STANDARD_TYPE(StepBasic_ApprovalRole), aRole);

  ent->Init(aPersonOrganization, aAuthorizedApproval, aRole);
}

void RWStepBasic_RWApprovalPersonOrganization::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepBasic_ApprovalPersonOrganization>& ent) const
{

  SW.Send(ent->PersonOrganization().Value());

  SW.Send(ent->AuthorizedApproval());

  SW.Send(ent->Role());
}

void RWStepBasic_RWApprovalPersonOrganization::Share(
  const occ::handle<StepBasic_ApprovalPersonOrganization>& ent,
  Interface_EntityIterator&                                iter) const
{

  iter.GetOneItem(ent->PersonOrganization().Value());

  iter.GetOneItem(ent->AuthorizedApproval());

  iter.GetOneItem(ent->Role());
}
