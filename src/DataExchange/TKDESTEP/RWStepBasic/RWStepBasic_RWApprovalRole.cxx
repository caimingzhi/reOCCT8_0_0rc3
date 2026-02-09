

#include "RWStepBasic_RWApprovalRole.hpp"
#include <StepBasic_ApprovalRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWApprovalRole::RWStepBasic_RWApprovalRole() = default;

void RWStepBasic_RWApprovalRole::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepBasic_ApprovalRole>&  ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "approval_role"))
    return;

  occ::handle<TCollection_HAsciiString> aRole;

  data->ReadString(num, 1, "role", ach, aRole);

  ent->Init(aRole);
}

void RWStepBasic_RWApprovalRole::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepBasic_ApprovalRole>& ent) const
{

  SW.Send(ent->Role());
}
