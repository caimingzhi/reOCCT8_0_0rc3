#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWNameAssignment.hpp"
#include <StepBasic_NameAssignment.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWNameAssignment::RWStepBasic_RWNameAssignment() = default;

void RWStepBasic_RWNameAssignment::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepBasic_NameAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "name_assignment"))
    return;

  occ::handle<TCollection_HAsciiString> aAssignedName;
  data->ReadString(num, 1, "assigned_name", ach, aAssignedName);

  ent->Init(aAssignedName);
}

void RWStepBasic_RWNameAssignment::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepBasic_NameAssignment>& ent) const
{

  SW.Send(ent->AssignedName());
}

void RWStepBasic_RWNameAssignment::Share(const occ::handle<StepBasic_NameAssignment>&,
                                         Interface_EntityIterator&) const
{
}
