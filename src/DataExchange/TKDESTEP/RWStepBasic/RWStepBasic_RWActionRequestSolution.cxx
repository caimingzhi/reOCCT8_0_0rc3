#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWActionRequestSolution.hpp"
#include <StepBasic_ActionMethod.hpp>
#include <StepBasic_ActionRequestSolution.hpp>
#include <StepBasic_VersionedActionRequest.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWActionRequestSolution::RWStepBasic_RWActionRequestSolution() = default;

//=================================================================================================

void RWStepBasic_RWActionRequestSolution::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepBasic_ActionRequestSolution>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "action_request_solution"))
    return;

  // Own fields of ActionRequestSolution

  occ::handle<StepBasic_ActionMethod> aMethod;
  data->ReadEntity(num, 1, "method", ach, STANDARD_TYPE(StepBasic_ActionMethod), aMethod);

  occ::handle<StepBasic_VersionedActionRequest> aRequest;
  data
    ->ReadEntity(num, 2, "request", ach, STANDARD_TYPE(StepBasic_VersionedActionRequest), aRequest);

  // Initialize entity
  ent->Init(aMethod, aRequest);
}

//=================================================================================================

void RWStepBasic_RWActionRequestSolution::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepBasic_ActionRequestSolution>& ent) const
{

  // Own fields of ActionRequestSolution

  SW.Send(ent->Method());

  SW.Send(ent->Request());
}

//=================================================================================================

void RWStepBasic_RWActionRequestSolution::Share(
  const occ::handle<StepBasic_ActionRequestSolution>& ent,
  Interface_EntityIterator&                           iter) const
{

  // Own fields of ActionRequestSolution

  iter.AddItem(ent->Method());

  iter.AddItem(ent->Request());
}
