#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWActionRequestAssignment.hpp"
#include <StepBasic_ActionRequestAssignment.hpp>
#include <StepBasic_VersionedActionRequest.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWActionRequestAssignment::RWStepBasic_RWActionRequestAssignment() = default;

//=================================================================================================

void RWStepBasic_RWActionRequestAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepBasic_ActionRequestAssignment>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "action_request_assignment"))
    return;

  // Own fields of ActionRequestAssignment

  occ::handle<StepBasic_VersionedActionRequest> aAssignedActionRequest;
  data->ReadEntity(num,
                   1,
                   "assigned_action_request",
                   ach,
                   STANDARD_TYPE(StepBasic_VersionedActionRequest),
                   aAssignedActionRequest);

  // Initialize entity
  ent->Init(aAssignedActionRequest);
}

//=================================================================================================

void RWStepBasic_RWActionRequestAssignment::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepBasic_ActionRequestAssignment>& ent) const
{

  // Own fields of ActionRequestAssignment

  SW.Send(ent->AssignedActionRequest());
}

//=================================================================================================

void RWStepBasic_RWActionRequestAssignment::Share(
  const occ::handle<StepBasic_ActionRequestAssignment>& ent,
  Interface_EntityIterator&                             iter) const
{

  // Own fields of ActionRequestAssignment

  iter.AddItem(ent->AssignedActionRequest());
}
