#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWIdentificationAssignment.hpp"
#include <StepBasic_IdentificationAssignment.hpp>
#include <StepBasic_IdentificationRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWIdentificationAssignment::RWStepBasic_RWIdentificationAssignment() = default;

void RWStepBasic_RWIdentificationAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepBasic_IdentificationAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "identification_assignment"))
    return;

  occ::handle<TCollection_HAsciiString> aAssignedId;
  data->ReadString(num, 1, "assigned_id", ach, aAssignedId);

  occ::handle<StepBasic_IdentificationRole> aRole;
  data->ReadEntity(num, 2, "role", ach, STANDARD_TYPE(StepBasic_IdentificationRole), aRole);

  ent->Init(aAssignedId, aRole);
}

void RWStepBasic_RWIdentificationAssignment::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepBasic_IdentificationAssignment>& ent) const
{

  SW.Send(ent->AssignedId());

  SW.Send(ent->Role());
}

void RWStepBasic_RWIdentificationAssignment::Share(
  const occ::handle<StepBasic_IdentificationAssignment>& ent,
  Interface_EntityIterator&                              iter) const
{

  iter.AddItem(ent->Role());
}
