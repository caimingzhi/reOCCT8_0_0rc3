

#include <StepAP214_AutoDesignPresentedItem.hpp>
#include <StepAP214_AutoDesignPresentedItemSelect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignPresentedItem, StepVisual_PresentedItem)

StepAP214_AutoDesignPresentedItem::StepAP214_AutoDesignPresentedItem() = default;

void StepAP214_AutoDesignPresentedItem::Init(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignPresentedItemSelect>>& aItems)
{

  items = aItems;
}

void StepAP214_AutoDesignPresentedItem::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignPresentedItemSelect>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignPresentedItemSelect>>
  StepAP214_AutoDesignPresentedItem::Items() const
{
  return items;
}

StepAP214_AutoDesignPresentedItemSelect StepAP214_AutoDesignPresentedItem::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignPresentedItem::NbItems() const
{
  if (items.IsNull())
    return 0;
  return items->Length();
}
