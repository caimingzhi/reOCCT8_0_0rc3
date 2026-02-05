#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWNameAssignment.hpp"
#include <StepBasic_NameAssignment.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWNameAssignment::RWStepBasic_RWNameAssignment() = default;

//=================================================================================================

void RWStepBasic_RWNameAssignment::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepBasic_NameAssignment>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "name_assignment"))
    return;

  // Own fields of NameAssignment

  occ::handle<TCollection_HAsciiString> aAssignedName;
  data->ReadString(num, 1, "assigned_name", ach, aAssignedName);

  // Initialize entity
  ent->Init(aAssignedName);
}

//=================================================================================================

void RWStepBasic_RWNameAssignment::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepBasic_NameAssignment>& ent) const
{

  // Own fields of NameAssignment

  SW.Send(ent->AssignedName());
}

//=================================================================================================

void RWStepBasic_RWNameAssignment::Share(const occ::handle<StepBasic_NameAssignment>&,
                                         Interface_EntityIterator&) const
{
  // Own fields of NameAssignment
}
