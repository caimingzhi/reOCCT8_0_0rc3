#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWActionAssignment.hpp"
#include <StepBasic_Action.hpp>
#include <StepBasic_ActionAssignment.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWActionAssignment::RWStepBasic_RWActionAssignment() = default;

void RWStepBasic_RWActionAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepBasic_ActionAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "action_assignment"))
    return;

  occ::handle<StepBasic_Action> aAssignedAction;
  data
    ->ReadEntity(num, 1, "assigned_action", ach, STANDARD_TYPE(StepBasic_Action), aAssignedAction);

  ent->Init(aAssignedAction);
}

void RWStepBasic_RWActionAssignment::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepBasic_ActionAssignment>& ent) const
{

  SW.Send(ent->AssignedAction());
}

void RWStepBasic_RWActionAssignment::Share(const occ::handle<StepBasic_ActionAssignment>& ent,
                                           Interface_EntityIterator& iter) const
{

  iter.AddItem(ent->AssignedAction());
}
