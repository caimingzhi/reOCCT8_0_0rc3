

#include <Standard_Type.hpp>
#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalAssignment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ApprovalAssignment, Standard_Transient)

void StepBasic_ApprovalAssignment::Init(const occ::handle<StepBasic_Approval>& aAssignedApproval)
{

  assignedApproval = aAssignedApproval;
}

void StepBasic_ApprovalAssignment::SetAssignedApproval(
  const occ::handle<StepBasic_Approval>& aAssignedApproval)
{
  assignedApproval = aAssignedApproval;
}

occ::handle<StepBasic_Approval> StepBasic_ApprovalAssignment::AssignedApproval() const
{
  return assignedApproval;
}
