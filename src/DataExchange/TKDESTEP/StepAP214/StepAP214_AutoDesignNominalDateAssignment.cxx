

#include <StepAP214_AutoDesignNominalDateAssignment.hpp>
#include <StepBasic_Date.hpp>
#include <StepBasic_DateRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignNominalDateAssignment, StepBasic_DateAssignment)

StepAP214_AutoDesignNominalDateAssignment::StepAP214_AutoDesignNominalDateAssignment() = default;

void StepAP214_AutoDesignNominalDateAssignment::Init(
  const occ::handle<StepBasic_Date>&                                     aAssignedDate,
  const occ::handle<StepBasic_DateRole>&                                 aRole,
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>>& aItems)
{

  items = aItems;

  StepBasic_DateAssignment::Init(aAssignedDate, aRole);
}

void StepAP214_AutoDesignNominalDateAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>>
  StepAP214_AutoDesignNominalDateAssignment::Items() const
{
  return items;
}

StepAP214_AutoDesignDatedItem StepAP214_AutoDesignNominalDateAssignment::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignNominalDateAssignment::NbItems() const
{
  return items->Length();
}
