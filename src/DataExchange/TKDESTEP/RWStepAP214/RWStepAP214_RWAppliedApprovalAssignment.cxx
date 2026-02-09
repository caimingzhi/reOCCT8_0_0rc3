

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAppliedApprovalAssignment.hpp"
#include <StepAP214_AppliedApprovalAssignment.hpp>
#include <StepAP214_ApprovalItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Approval.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAppliedApprovalAssignment::RWStepAP214_RWAppliedApprovalAssignment() = default;

void RWStepAP214_RWAppliedApprovalAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&             data,
  const int                                               num,
  occ::handle<Interface_Check>&                           ach,
  const occ::handle<StepAP214_AppliedApprovalAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "applied_approval_assignment"))
    return;

  occ::handle<StepBasic_Approval> aAssignedApproval;
  data->ReadEntity(num,
                   1,
                   "assigned_approval",
                   ach,
                   STANDARD_TYPE(StepBasic_Approval),
                   aAssignedApproval);

  occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>> aItems;
  StepAP214_ApprovalItem                                   aItemsItem;
  int                                                      nsub2;
  if (data->ReadSubList(num, 2, "items", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aItems  = new NCollection_HArray1<StepAP214_ApprovalItem>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {
      bool stat2 = data->ReadEntity(nsub2, i2, "items", ach, aItemsItem);
      if (stat2)
        aItems->SetValue(i2, aItemsItem);
    }
  }

  ent->Init(aAssignedApproval, aItems);
}

void RWStepAP214_RWAppliedApprovalAssignment::WriteStep(
  StepData_StepWriter&                                    SW,
  const occ::handle<StepAP214_AppliedApprovalAssignment>& ent) const
{

  SW.Send(ent->AssignedApproval());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbItems(); i2++)
  {
    SW.Send(ent->ItemsValue(i2).Value());
  }
  SW.CloseSub();
}

void RWStepAP214_RWAppliedApprovalAssignment::Share(
  const occ::handle<StepAP214_AppliedApprovalAssignment>& ent,
  Interface_EntityIterator&                               iter) const
{

  iter.GetOneItem(ent->AssignedApproval());
  int nbElem2 = ent->NbItems();
  for (int is2 = 1; is2 <= nbElem2; is2++)
  {
    iter.GetOneItem(ent->ItemsValue(is2).Value());
  }
}
