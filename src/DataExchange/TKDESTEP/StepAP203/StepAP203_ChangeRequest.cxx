#include <StepAP203_ChangeRequest.hpp>
#include <StepBasic_VersionedActionRequest.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_ChangeRequest, StepBasic_ActionRequestAssignment)

StepAP203_ChangeRequest::StepAP203_ChangeRequest() = default;

void StepAP203_ChangeRequest::Init(
  const occ::handle<StepBasic_VersionedActionRequest>&
    aActionRequestAssignment_AssignedActionRequest,
  const occ::handle<NCollection_HArray1<StepAP203_ChangeRequestItem>>& aItems)
{
  StepBasic_ActionRequestAssignment::Init(aActionRequestAssignment_AssignedActionRequest);

  theItems = aItems;
}

occ::handle<NCollection_HArray1<StepAP203_ChangeRequestItem>> StepAP203_ChangeRequest::Items() const
{
  return theItems;
}

void StepAP203_ChangeRequest::SetItems(
  const occ::handle<NCollection_HArray1<StepAP203_ChangeRequestItem>>& aItems)
{
  theItems = aItems;
}
