

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWApproval.hpp"
#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalStatus.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWApproval::RWStepBasic_RWApproval() = default;

void RWStepBasic_RWApproval::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepBasic_Approval>&      ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "approval"))
    return;

  occ::handle<StepBasic_ApprovalStatus> aStatus;

  data->ReadEntity(num, 1, "status", ach, STANDARD_TYPE(StepBasic_ApprovalStatus), aStatus);

  occ::handle<TCollection_HAsciiString> aLevel;

  data->ReadString(num, 2, "level", ach, aLevel);

  ent->Init(aStatus, aLevel);
}

void RWStepBasic_RWApproval::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepBasic_Approval>& ent) const
{

  SW.Send(ent->Status());

  SW.Send(ent->Level());
}

void RWStepBasic_RWApproval::Share(const occ::handle<StepBasic_Approval>& ent,
                                   Interface_EntityIterator&              iter) const
{

  iter.GetOneItem(ent->Status());
}
