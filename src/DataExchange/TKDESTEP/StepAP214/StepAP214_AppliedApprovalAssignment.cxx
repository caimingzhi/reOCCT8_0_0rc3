

#include <StepAP214_AppliedApprovalAssignment.hpp>
#include <StepAP214_ApprovalItem.hpp>
#include <StepBasic_Approval.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AppliedApprovalAssignment, StepBasic_ApprovalAssignment)

StepAP214_AppliedApprovalAssignment::StepAP214_AppliedApprovalAssignment() = default;

void StepAP214_AppliedApprovalAssignment::Init(
  const occ::handle<StepBasic_Approval>&                          aAssignedApproval,
  const occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>>& aItems)
{

  items = aItems;

  StepBasic_ApprovalAssignment::Init(aAssignedApproval);
}

void StepAP214_AppliedApprovalAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>> StepAP214_AppliedApprovalAssignment::
  Items() const
{
  return items;
}

StepAP214_ApprovalItem StepAP214_AppliedApprovalAssignment::ItemsValue(const int num) const
{
  return items->Value(num);
}

int StepAP214_AppliedApprovalAssignment::NbItems() const
{
  return items->Length();
}
