

#include <StepVisual_Invisibility.hpp>
#include <StepVisual_InvisibleItem.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_Invisibility, Standard_Transient)

StepVisual_Invisibility::StepVisual_Invisibility() = default;

void StepVisual_Invisibility::Init(
  const occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>>& aInvisibleItems)
{

  invisibleItems = aInvisibleItems;
}

void StepVisual_Invisibility::SetInvisibleItems(
  const occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>>& aInvisibleItems)
{
  invisibleItems = aInvisibleItems;
}

occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>> StepVisual_Invisibility::InvisibleItems()
  const
{
  return invisibleItems;
}

StepVisual_InvisibleItem StepVisual_Invisibility::InvisibleItemsValue(const int num) const
{
  return invisibleItems->Value(num);
}

int StepVisual_Invisibility::NbInvisibleItems() const
{
  return invisibleItems->Length();
}
