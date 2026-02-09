

#include <StepAP214_AppliedDateAssignment.hpp>
#include <StepAP214_DateItem.hpp>
#include <StepBasic_Date.hpp>
#include <StepBasic_DateRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AppliedDateAssignment, StepBasic_DateAssignment)

StepAP214_AppliedDateAssignment::StepAP214_AppliedDateAssignment() = default;

void StepAP214_AppliedDateAssignment::Init(
  const occ::handle<StepBasic_Date>&                          aAssignedDate,
  const occ::handle<StepBasic_DateRole>&                      aRole,
  const occ::handle<NCollection_HArray1<StepAP214_DateItem>>& aItems)
{

  items = aItems;

  StepBasic_DateAssignment::Init(aAssignedDate, aRole);
}

void StepAP214_AppliedDateAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_DateItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_DateItem>> StepAP214_AppliedDateAssignment::Items() const
{
  return items;
}

StepAP214_DateItem StepAP214_AppliedDateAssignment::ItemsValue(const int num) const
{
  return items->Value(num);
}

int StepAP214_AppliedDateAssignment::NbItems() const
{
  return items->Length();
}
