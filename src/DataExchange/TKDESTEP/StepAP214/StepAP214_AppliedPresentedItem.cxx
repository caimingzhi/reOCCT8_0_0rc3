

#include <StepAP214_AppliedPresentedItem.hpp>
#include <StepAP214_PresentedItemSelect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AppliedPresentedItem, StepVisual_PresentedItem)

StepAP214_AppliedPresentedItem::StepAP214_AppliedPresentedItem() = default;

void StepAP214_AppliedPresentedItem::Init(
  const occ::handle<NCollection_HArray1<StepAP214_PresentedItemSelect>>& aItems)
{

  items = aItems;
}

void StepAP214_AppliedPresentedItem::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_PresentedItemSelect>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_PresentedItemSelect>> StepAP214_AppliedPresentedItem::
  Items() const
{
  return items;
}

StepAP214_PresentedItemSelect StepAP214_AppliedPresentedItem::ItemsValue(const int num) const
{
  return items->Value(num);
}

int StepAP214_AppliedPresentedItem::NbItems() const
{
  if (items.IsNull())
    return 0;
  return items->Length();
}
