

#include "RWStepBasic_RWApprovalStatus.hpp"
#include <StepBasic_ApprovalStatus.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWApprovalStatus::RWStepBasic_RWApprovalStatus() = default;

void RWStepBasic_RWApprovalStatus::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepBasic_ApprovalStatus>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "approval_status"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepBasic_RWApprovalStatus::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepBasic_ApprovalStatus>& ent) const
{

  SW.Send(ent->Name());
}
