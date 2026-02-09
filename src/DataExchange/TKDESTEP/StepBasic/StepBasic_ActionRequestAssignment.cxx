#include <Standard_Type.hpp>
#include <StepBasic_ActionRequestAssignment.hpp>
#include <StepBasic_VersionedActionRequest.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ActionRequestAssignment, Standard_Transient)

StepBasic_ActionRequestAssignment::StepBasic_ActionRequestAssignment() = default;

void StepBasic_ActionRequestAssignment::Init(
  const occ::handle<StepBasic_VersionedActionRequest>& aAssignedActionRequest)
{

  theAssignedActionRequest = aAssignedActionRequest;
}

occ::handle<StepBasic_VersionedActionRequest> StepBasic_ActionRequestAssignment::
  AssignedActionRequest() const
{
  return theAssignedActionRequest;
}

void StepBasic_ActionRequestAssignment::SetAssignedActionRequest(
  const occ::handle<StepBasic_VersionedActionRequest>& aAssignedActionRequest)
{
  theAssignedActionRequest = aAssignedActionRequest;
}
