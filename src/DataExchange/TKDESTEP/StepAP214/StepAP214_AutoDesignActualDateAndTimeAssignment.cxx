

#include <StepAP214_AutoDesignActualDateAndTimeAssignment.hpp>
#include <StepAP214_AutoDesignDateAndTimeItem.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_DateTimeRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignActualDateAndTimeAssignment,
                           StepBasic_DateAndTimeAssignment)

StepAP214_AutoDesignActualDateAndTimeAssignment::StepAP214_AutoDesignActualDateAndTimeAssignment() =
  default;

void StepAP214_AutoDesignActualDateAndTimeAssignment::Init(
  const occ::handle<StepBasic_DateAndTime>&                                    aAssignedDateAndTime,
  const occ::handle<StepBasic_DateTimeRole>&                                   aRole,
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>>& aItems)
{

  items = aItems;

  StepBasic_DateAndTimeAssignment::Init(aAssignedDateAndTime, aRole);
}

void StepAP214_AutoDesignActualDateAndTimeAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>>
  StepAP214_AutoDesignActualDateAndTimeAssignment::Items() const
{
  return items;
}

StepAP214_AutoDesignDateAndTimeItem StepAP214_AutoDesignActualDateAndTimeAssignment::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignActualDateAndTimeAssignment::NbItems() const
{
  return items->Length();
}
