#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP203_RWCcDesignApproval.hpp"
#include <StepAP203_CcDesignApproval.hpp>
#include <StepAP203_ApprovedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Approval.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP203_RWCcDesignApproval::RWStepAP203_RWCcDesignApproval() = default;

void RWStepAP203_RWCcDesignApproval::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepAP203_CcDesignApproval>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "cc_design_approval"))
    return;

  occ::handle<StepBasic_Approval> aApprovalAssignment_AssignedApproval;
  data->ReadEntity(num,
                   1,
                   "approval_assignment.assigned_approval",
                   ach,
                   STANDARD_TYPE(StepBasic_Approval),
                   aApprovalAssignment_AssignedApproval);

  occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> aItems;
  int                                                      sub2 = 0;
  if (data->ReadSubList(num, 2, "items", ach, sub2))
  {
    int num2 = sub2;
    int nb0  = data->NbParams(num2);
    aItems   = new NCollection_HArray1<StepAP203_ApprovedItem>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepAP203_ApprovedItem anIt0;
      data->ReadEntity(num2, i0, "items", ach, anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  ent->Init(aApprovalAssignment_AssignedApproval, aItems);
}

void RWStepAP203_RWCcDesignApproval::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepAP203_CcDesignApproval>& ent) const
{

  SW.Send(ent->StepBasic_ApprovalAssignment::AssignedApproval());

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->Items()->Length(); i1++)
  {
    StepAP203_ApprovedItem Var0 = ent->Items()->Value(i1);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

void RWStepAP203_RWCcDesignApproval::Share(const occ::handle<StepAP203_CcDesignApproval>& ent,
                                           Interface_EntityIterator& iter) const
{

  iter.AddItem(ent->StepBasic_ApprovalAssignment::AssignedApproval());

  for (int i2 = 1; i2 <= ent->Items()->Length(); i2++)
  {
    StepAP203_ApprovedItem Var0 = ent->Items()->Value(i2);
    iter.AddItem(Var0.Value());
  }
}
