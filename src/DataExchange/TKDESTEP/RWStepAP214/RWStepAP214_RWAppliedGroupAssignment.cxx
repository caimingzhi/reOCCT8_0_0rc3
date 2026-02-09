#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAppliedGroupAssignment.hpp"
#include <StepAP214_AppliedGroupAssignment.hpp>
#include <StepAP214_GroupItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Group.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAppliedGroupAssignment::RWStepAP214_RWAppliedGroupAssignment() = default;

void RWStepAP214_RWAppliedGroupAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepAP214_AppliedGroupAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "applied_group_assignment"))
    return;

  occ::handle<StepBasic_Group> aGroupAssignment_AssignedGroup;
  data->ReadEntity(num,
                   1,
                   "group_assignment.assigned_group",
                   ach,
                   STANDARD_TYPE(StepBasic_Group),
                   aGroupAssignment_AssignedGroup);

  occ::handle<NCollection_HArray1<StepAP214_GroupItem>> anItems;
  int                                                   sub2 = 0;
  if (data->ReadSubList(num, 2, "items", ach, sub2))
  {
    int num2 = sub2;
    int nb0  = data->NbParams(num2);
    if (nb0)
    {
      anItems = new NCollection_HArray1<StepAP214_GroupItem>(1, nb0);
      for (int i0 = 1; i0 <= nb0; i0++)
      {
        StepAP214_GroupItem anIt0;
        data->ReadEntity(num2, i0, "items", ach, anIt0);
        anItems->SetValue(i0, anIt0);
      }
    }
  }

  ent->Init(aGroupAssignment_AssignedGroup, anItems);
}

void RWStepAP214_RWAppliedGroupAssignment::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepAP214_AppliedGroupAssignment>& ent) const
{

  SW.Send(ent->StepBasic_GroupAssignment::AssignedGroup());

  SW.OpenSub();
  if (!ent->Items().IsNull())
  {
    for (int i1 = 1; i1 <= ent->Items()->Length(); i1++)
    {
      StepAP214_GroupItem Var0 = ent->Items()->Value(i1);
      SW.Send(Var0.Value());
    }
  }
  SW.CloseSub();
}

void RWStepAP214_RWAppliedGroupAssignment::Share(
  const occ::handle<StepAP214_AppliedGroupAssignment>& ent,
  Interface_EntityIterator&                            iter) const
{

  iter.AddItem(ent->StepBasic_GroupAssignment::AssignedGroup());

  if (!ent->Items().IsNull())
  {
    for (int i2 = 1; i2 <= ent->Items()->Length(); i2++)
    {
      StepAP214_GroupItem Var0 = ent->Items()->Value(i2);
      iter.AddItem(Var0.Value());
    }
  }
}
