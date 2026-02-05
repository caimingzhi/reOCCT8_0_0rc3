#include <StepAP203_CcDesignApproval.hpp>
#include <StepBasic_Approval.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_CcDesignApproval, StepBasic_ApprovalAssignment)

//=================================================================================================

StepAP203_CcDesignApproval::StepAP203_CcDesignApproval() = default;

//=================================================================================================

void StepAP203_CcDesignApproval::Init(
  const occ::handle<StepBasic_Approval>& aApprovalAssignment_AssignedApproval,
  const occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>>& aItems)
{
  StepBasic_ApprovalAssignment::Init(aApprovalAssignment_AssignedApproval);

  theItems = aItems;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> StepAP203_CcDesignApproval::Items() const
{
  return theItems;
}

//=================================================================================================

void StepAP203_CcDesignApproval::SetItems(
  const occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>>& aItems)
{
  theItems = aItems;
}
