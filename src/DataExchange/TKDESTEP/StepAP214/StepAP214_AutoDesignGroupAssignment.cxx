

#include <StepAP214_AutoDesignGroupAssignment.hpp>
#include <StepAP214_AutoDesignGroupedItem.hpp>
#include <StepBasic_Group.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignGroupAssignment, StepBasic_GroupAssignment)

StepAP214_AutoDesignGroupAssignment::StepAP214_AutoDesignGroupAssignment() = default;

void StepAP214_AutoDesignGroupAssignment::Init(
  const occ::handle<StepBasic_Group>&                                      aAssignedGroup,
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGroupedItem>>& aItems)
{

  items = aItems;

  StepBasic_GroupAssignment::Init(aAssignedGroup);
}

void StepAP214_AutoDesignGroupAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGroupedItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignGroupedItem>>
  StepAP214_AutoDesignGroupAssignment::Items() const
{
  return items;
}

StepAP214_AutoDesignGroupedItem StepAP214_AutoDesignGroupAssignment::ItemsValue(const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignGroupAssignment::NbItems() const
{
  return items->Length();
}
