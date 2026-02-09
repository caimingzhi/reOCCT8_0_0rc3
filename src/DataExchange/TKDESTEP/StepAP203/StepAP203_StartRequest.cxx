#include <StepAP203_StartRequest.hpp>
#include <StepBasic_VersionedActionRequest.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_StartRequest, StepBasic_ActionRequestAssignment)

StepAP203_StartRequest::StepAP203_StartRequest() = default;

void StepAP203_StartRequest::Init(
  const occ::handle<StepBasic_VersionedActionRequest>&
    aActionRequestAssignment_AssignedActionRequest,
  const occ::handle<NCollection_HArray1<StepAP203_StartRequestItem>>& aItems)
{
  StepBasic_ActionRequestAssignment::Init(aActionRequestAssignment_AssignedActionRequest);

  theItems = aItems;
}

occ::handle<NCollection_HArray1<StepAP203_StartRequestItem>> StepAP203_StartRequest::Items() const
{
  return theItems;
}

void StepAP203_StartRequest::SetItems(
  const occ::handle<NCollection_HArray1<StepAP203_StartRequestItem>>& aItems)
{
  theItems = aItems;
}
