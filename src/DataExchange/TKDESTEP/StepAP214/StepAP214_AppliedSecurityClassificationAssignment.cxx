

#include <StepAP214_AppliedSecurityClassificationAssignment.hpp>
#include <StepAP214_SecurityClassificationItem.hpp>
#include <StepBasic_SecurityClassification.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AppliedSecurityClassificationAssignment,
                           StepBasic_SecurityClassificationAssignment)

StepAP214_AppliedSecurityClassificationAssignment::
  StepAP214_AppliedSecurityClassificationAssignment() = default;

void StepAP214_AppliedSecurityClassificationAssignment::Init(
  const occ::handle<StepBasic_SecurityClassification>& aAssignedSecurityClassification,
  const occ::handle<NCollection_HArray1<StepAP214_SecurityClassificationItem>>& aItems)
{

  items = aItems;

  StepBasic_SecurityClassificationAssignment::Init(aAssignedSecurityClassification);
}

void StepAP214_AppliedSecurityClassificationAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_SecurityClassificationItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_SecurityClassificationItem>>
  StepAP214_AppliedSecurityClassificationAssignment::Items() const
{
  return items;
}

const StepAP214_SecurityClassificationItem& StepAP214_AppliedSecurityClassificationAssignment::
  ItemsValue(const int num) const
{
  return items->Value(num);
}

int StepAP214_AppliedSecurityClassificationAssignment::NbItems() const
{
  if (items.IsNull())
    return 0;
  return items->Length();
}
