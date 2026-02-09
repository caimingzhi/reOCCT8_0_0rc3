

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWApprovalRelationship.hpp"
#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalRelationship.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWApprovalRelationship::RWStepBasic_RWApprovalRelationship() = default;

void RWStepBasic_RWApprovalRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepBasic_ApprovalRelationship>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "approval_relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "description", ach, aDescription);
  }

  occ::handle<StepBasic_Approval> aRelatingApproval;

  data->ReadEntity(num,
                   3,
                   "relating_approval",
                   ach,
                   STANDARD_TYPE(StepBasic_Approval),
                   aRelatingApproval);

  occ::handle<StepBasic_Approval> aRelatedApproval;

  data->ReadEntity(num,
                   4,
                   "related_approval",
                   ach,
                   STANDARD_TYPE(StepBasic_Approval),
                   aRelatedApproval);

  ent->Init(aName, aDescription, aRelatingApproval, aRelatedApproval);
}

void RWStepBasic_RWApprovalRelationship::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepBasic_ApprovalRelationship>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->RelatingApproval());

  SW.Send(ent->RelatedApproval());
}

void RWStepBasic_RWApprovalRelationship::Share(
  const occ::handle<StepBasic_ApprovalRelationship>& ent,
  Interface_EntityIterator&                          iter) const
{

  iter.GetOneItem(ent->RelatingApproval());

  iter.GetOneItem(ent->RelatedApproval());
}
