

#include <StepAP214_AppliedDateAndTimeAssignment.hpp>
#include <StepAP214_DateAndTimeItem.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_DateTimeRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AppliedDateAndTimeAssignment, StepBasic_DateAndTimeAssignment)

StepAP214_AppliedDateAndTimeAssignment::StepAP214_AppliedDateAndTimeAssignment() = default;

void StepAP214_AppliedDateAndTimeAssignment::Init(
  const occ::handle<StepBasic_DateAndTime>&                          aAssignedDateAndTime,
  const occ::handle<StepBasic_DateTimeRole>&                         aRole,
  const occ::handle<NCollection_HArray1<StepAP214_DateAndTimeItem>>& aItems)
{

  items = aItems;

  StepBasic_DateAndTimeAssignment::Init(aAssignedDateAndTime, aRole);
}

void StepAP214_AppliedDateAndTimeAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_DateAndTimeItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_DateAndTimeItem>> StepAP214_AppliedDateAndTimeAssignment::
  Items() const
{
  return items;
}

StepAP214_DateAndTimeItem StepAP214_AppliedDateAndTimeAssignment::ItemsValue(const int num) const
{
  return items->Value(num);
}

int StepAP214_AppliedDateAndTimeAssignment::NbItems() const
{
  return items->Length();
}
