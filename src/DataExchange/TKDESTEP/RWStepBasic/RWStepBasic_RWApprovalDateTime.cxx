

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWApprovalDateTime.hpp"
#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalDateTime.hpp>
#include <StepBasic_DateTimeSelect.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWApprovalDateTime::RWStepBasic_RWApprovalDateTime() = default;

void RWStepBasic_RWApprovalDateTime::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepBasic_ApprovalDateTime>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "approval_date_time"))
    return;

  StepBasic_DateTimeSelect dts;

  data->ReadEntity(num, 1, "date_time", ach, dts);

  occ::handle<StepBasic_Approval> ap;

  data->ReadEntity(num, 2, "dated_approval", ach, STANDARD_TYPE(StepBasic_Approval), ap);

  ent->Init(dts, ap);
}

void RWStepBasic_RWApprovalDateTime::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepBasic_ApprovalDateTime>& ent) const
{

  SW.Send(ent->DateTime().Value());
  SW.Send(ent->DatedApproval());
}

void RWStepBasic_RWApprovalDateTime::Share(const occ::handle<StepBasic_ApprovalDateTime>& ent,
                                           Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->DateTime().Value());
  iter.GetOneItem(ent->DatedApproval());
}
