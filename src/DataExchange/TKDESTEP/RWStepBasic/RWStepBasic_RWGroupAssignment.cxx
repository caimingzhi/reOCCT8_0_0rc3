#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWGroupAssignment.hpp"
#include <StepBasic_Group.hpp>
#include <StepBasic_GroupAssignment.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWGroupAssignment::RWStepBasic_RWGroupAssignment() = default;

//=================================================================================================

void RWStepBasic_RWGroupAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepBasic_GroupAssignment>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "group_assignment"))
    return;

  // Own fields of GroupAssignment

  occ::handle<StepBasic_Group> aAssignedGroup;
  data->ReadEntity(num, 1, "assigned_group", ach, STANDARD_TYPE(StepBasic_Group), aAssignedGroup);

  // Initialize entity
  ent->Init(aAssignedGroup);
}

//=================================================================================================

void RWStepBasic_RWGroupAssignment::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepBasic_GroupAssignment>& ent) const
{

  // Own fields of GroupAssignment

  SW.Send(ent->AssignedGroup());
}

//=================================================================================================

void RWStepBasic_RWGroupAssignment::Share(const occ::handle<StepBasic_GroupAssignment>& ent,
                                          Interface_EntityIterator&                     iter) const
{

  // Own fields of GroupAssignment

  iter.AddItem(ent->AssignedGroup());
}
