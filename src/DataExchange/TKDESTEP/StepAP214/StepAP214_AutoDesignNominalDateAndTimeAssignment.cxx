

#include <StepAP214_AutoDesignNominalDateAndTimeAssignment.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_DateTimeRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignNominalDateAndTimeAssignment,
                           StepBasic_DateAndTimeAssignment)

StepAP214_AutoDesignNominalDateAndTimeAssignment::
  StepAP214_AutoDesignNominalDateAndTimeAssignment() = default;

void StepAP214_AutoDesignNominalDateAndTimeAssignment::Init(
  const occ::handle<StepBasic_DateAndTime>&                                    aAssignedDateAndTime,
  const occ::handle<StepBasic_DateTimeRole>&                                   aRole,
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>>& aItems)
{

  items = aItems;

  StepBasic_DateAndTimeAssignment::Init(aAssignedDateAndTime, aRole);
}

void StepAP214_AutoDesignNominalDateAndTimeAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>>
  StepAP214_AutoDesignNominalDateAndTimeAssignment::Items() const
{
  return items;
}

StepAP214_AutoDesignDateAndTimeItem StepAP214_AutoDesignNominalDateAndTimeAssignment::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignNominalDateAndTimeAssignment::NbItems() const
{
  return items->Length();
}
