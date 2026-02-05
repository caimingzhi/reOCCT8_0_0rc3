#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP203_RWStartWork.hpp"
#include <StepAP203_StartWork.hpp>
#include <StepAP203_WorkItem.hpp>
#include <StepBasic_Action.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepAP203_RWStartWork::RWStepAP203_RWStartWork() = default;

//=================================================================================================

void RWStepAP203_RWStartWork::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                       const int                                   num,
                                       occ::handle<Interface_Check>&               ach,
                                       const occ::handle<StepAP203_StartWork>&     ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "start_work"))
    return;

  // Inherited fields of ActionAssignment

  occ::handle<StepBasic_Action> aActionAssignment_AssignedAction;
  data->ReadEntity(num,
                   1,
                   "action_assignment.assigned_action",
                   ach,
                   STANDARD_TYPE(StepBasic_Action),
                   aActionAssignment_AssignedAction);

  // Own fields of StartWork

  occ::handle<NCollection_HArray1<StepAP203_WorkItem>> aItems;
  int                                                  sub2 = 0;
  if (data->ReadSubList(num, 2, "items", ach, sub2))
  {
    int num2 = sub2;
    int nb0  = data->NbParams(num2);
    aItems   = new NCollection_HArray1<StepAP203_WorkItem>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepAP203_WorkItem anIt0;
      data->ReadEntity(num2, i0, "items", ach, anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aActionAssignment_AssignedAction, aItems);
}

//=================================================================================================

void RWStepAP203_RWStartWork::WriteStep(StepData_StepWriter&                    SW,
                                        const occ::handle<StepAP203_StartWork>& ent) const
{

  // Inherited fields of ActionAssignment

  SW.Send(ent->StepBasic_ActionAssignment::AssignedAction());

  // Own fields of StartWork

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->Items()->Length(); i1++)
  {
    StepAP203_WorkItem Var0 = ent->Items()->Value(i1);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepAP203_RWStartWork::Share(const occ::handle<StepAP203_StartWork>& ent,
                                    Interface_EntityIterator&               iter) const
{

  // Inherited fields of ActionAssignment

  iter.AddItem(ent->StepBasic_ActionAssignment::AssignedAction());

  // Own fields of StartWork

  for (int i2 = 1; i2 <= ent->Items()->Length(); i2++)
  {
    StepAP203_WorkItem Var0 = ent->Items()->Value(i2);
    iter.AddItem(Var0.Value());
  }
}
