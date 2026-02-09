

#include <StepAP214_AutoDesignActualDateAssignment.hpp>
#include <StepAP214_AutoDesignDatedItem.hpp>
#include <StepBasic_Date.hpp>
#include <StepBasic_DateRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignActualDateAssignment, StepBasic_DateAssignment)

StepAP214_AutoDesignActualDateAssignment::StepAP214_AutoDesignActualDateAssignment() = default;

void StepAP214_AutoDesignActualDateAssignment::Init(
  const occ::handle<StepBasic_Date>&                                     aAssignedDate,
  const occ::handle<StepBasic_DateRole>&                                 aRole,
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>>& aItems)
{

  items = aItems;

  StepBasic_DateAssignment::Init(aAssignedDate, aRole);
}

void StepAP214_AutoDesignActualDateAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>>
  StepAP214_AutoDesignActualDateAssignment::Items() const
{
  return items;
}

StepAP214_AutoDesignDatedItem StepAP214_AutoDesignActualDateAssignment::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignActualDateAssignment::NbItems() const
{
  return items->Length();
}
