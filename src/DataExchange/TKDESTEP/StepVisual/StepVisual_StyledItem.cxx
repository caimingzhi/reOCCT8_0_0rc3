

#include <StepVisual_StyledItem.hpp>
#include <StepVisual_StyledItemTarget.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_StyledItem, StepRepr_RepresentationItem)

void StepVisual_StyledItem::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                         aStyles,
  const occ::handle<Standard_Transient>& aItem)
{

  myStyles   = aStyles;
  myItem     = aItem;
  myReprItem = occ::down_cast<StepRepr_RepresentationItem>(aItem);

  StepRepr_RepresentationItem::Init(aName);
}

void StepVisual_StyledItem::SetStyles(
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
    aStyles)
{
  myStyles = aStyles;
}

void StepVisual_StyledItem::SetItem(const occ::handle<StepRepr_RepresentationItem>& aItem)
{
  myItem     = aItem;
  myReprItem = aItem;
}

void StepVisual_StyledItem::SetItem(const StepVisual_StyledItemTarget& theItem)
{
  myItem     = theItem.Value();
  myReprItem = occ::down_cast<StepRepr_RepresentationItem>(myItem);
}

StepVisual_StyledItemTarget StepVisual_StyledItem::ItemAP242() const
{
  StepVisual_StyledItemTarget anItem;
  if (anItem.CaseNum(myItem) > 0)
    anItem.SetValue(myItem);
  return anItem;
}
