#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP203_RWStartRequest.hpp"
#include <StepAP203_StartRequest.hpp>
#include <StepAP203_StartRequestItem.hpp>
#include <StepBasic_VersionedActionRequest.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepAP203_RWStartRequest::RWStepAP203_RWStartRequest() = default;

//=================================================================================================

void RWStepAP203_RWStartRequest::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepAP203_StartRequest>&  ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "start_request"))
    return;

  // Inherited fields of ActionRequestAssignment

  occ::handle<StepBasic_VersionedActionRequest> aActionRequestAssignment_AssignedActionRequest;
  data->ReadEntity(num,
                   1,
                   "action_request_assignment.assigned_action_request",
                   ach,
                   STANDARD_TYPE(StepBasic_VersionedActionRequest),
                   aActionRequestAssignment_AssignedActionRequest);

  // Own fields of StartRequest

  occ::handle<NCollection_HArray1<StepAP203_StartRequestItem>> aItems;
  int                                                          sub2 = 0;
  if (data->ReadSubList(num, 2, "items", ach, sub2))
  {
    int num2 = sub2;
    int nb0  = data->NbParams(num2);
    aItems   = new NCollection_HArray1<StepAP203_StartRequestItem>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepAP203_StartRequestItem anIt0;
      data->ReadEntity(num2, i0, "items", ach, anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aActionRequestAssignment_AssignedActionRequest, aItems);
}

//=================================================================================================

void RWStepAP203_RWStartRequest::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepAP203_StartRequest>& ent) const
{

  // Inherited fields of ActionRequestAssignment

  SW.Send(ent->StepBasic_ActionRequestAssignment::AssignedActionRequest());

  // Own fields of StartRequest

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->Items()->Length(); i1++)
  {
    StepAP203_StartRequestItem Var0 = ent->Items()->Value(i1);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepAP203_RWStartRequest::Share(const occ::handle<StepAP203_StartRequest>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  // Inherited fields of ActionRequestAssignment

  iter.AddItem(ent->StepBasic_ActionRequestAssignment::AssignedActionRequest());

  // Own fields of StartRequest

  for (int i2 = 1; i2 <= ent->Items()->Length(); i2++)
  {
    StepAP203_StartRequestItem Var0 = ent->Items()->Value(i2);
    iter.AddItem(Var0.Value());
  }
}
