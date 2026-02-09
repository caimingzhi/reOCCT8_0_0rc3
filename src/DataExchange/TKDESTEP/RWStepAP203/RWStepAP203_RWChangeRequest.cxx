#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP203_RWChangeRequest.hpp"
#include <StepAP203_ChangeRequest.hpp>
#include <StepAP203_ChangeRequestItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_VersionedActionRequest.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP203_RWChangeRequest::RWStepAP203_RWChangeRequest() = default;

void RWStepAP203_RWChangeRequest::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepAP203_ChangeRequest>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "change_request"))
    return;

  occ::handle<StepBasic_VersionedActionRequest> aActionRequestAssignment_AssignedActionRequest;
  data->ReadEntity(num,
                   1,
                   "action_request_assignment.assigned_action_request",
                   ach,
                   STANDARD_TYPE(StepBasic_VersionedActionRequest),
                   aActionRequestAssignment_AssignedActionRequest);

  occ::handle<NCollection_HArray1<StepAP203_ChangeRequestItem>> aItems;
  int                                                           sub2 = 0;
  if (data->ReadSubList(num, 2, "items", ach, sub2))
  {
    int num2 = sub2;
    int nb0  = data->NbParams(num2);
    aItems   = new NCollection_HArray1<StepAP203_ChangeRequestItem>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepAP203_ChangeRequestItem anIt0;
      data->ReadEntity(num2, i0, "items", ach, anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  ent->Init(aActionRequestAssignment_AssignedActionRequest, aItems);
}

void RWStepAP203_RWChangeRequest::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepAP203_ChangeRequest>& ent) const
{

  SW.Send(ent->StepBasic_ActionRequestAssignment::AssignedActionRequest());

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->Items()->Length(); i1++)
  {
    StepAP203_ChangeRequestItem Var0 = ent->Items()->Value(i1);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

void RWStepAP203_RWChangeRequest::Share(const occ::handle<StepAP203_ChangeRequest>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  iter.AddItem(ent->StepBasic_ActionRequestAssignment::AssignedActionRequest());

  for (int i2 = 1; i2 <= ent->Items()->Length(); i2++)
  {
    StepAP203_ChangeRequestItem Var0 = ent->Items()->Value(i2);
    iter.AddItem(Var0.Value());
  }
}
