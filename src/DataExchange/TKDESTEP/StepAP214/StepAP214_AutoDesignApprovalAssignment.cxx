

#include <StepAP214_AutoDesignApprovalAssignment.hpp>
#include <StepAP214_AutoDesignGeneralOrgItem.hpp>
#include <StepBasic_Approval.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignApprovalAssignment, StepBasic_ApprovalAssignment)

StepAP214_AutoDesignApprovalAssignment::StepAP214_AutoDesignApprovalAssignment() = default;

void StepAP214_AutoDesignApprovalAssignment::Init(
  const occ::handle<StepBasic_Approval>&                                      aAssignedApproval,
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>& aItems)
{

  items = aItems;

  StepBasic_ApprovalAssignment::Init(aAssignedApproval);
}

void StepAP214_AutoDesignApprovalAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>
  StepAP214_AutoDesignApprovalAssignment::Items() const
{
  return items;
}

StepAP214_AutoDesignGeneralOrgItem StepAP214_AutoDesignApprovalAssignment::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignApprovalAssignment::NbItems() const
{
  return items->Length();
}
