

#include <StepVisual_OverRidingStyledItem.hpp>
#include <StepVisual_StyledItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_OverRidingStyledItem, StepVisual_StyledItem)

StepVisual_OverRidingStyledItem::StepVisual_OverRidingStyledItem() = default;

void StepVisual_OverRidingStyledItem::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                            aStyles,
  const occ::handle<Standard_Transient>&    aItem,
  const occ::handle<StepVisual_StyledItem>& aOverRiddenStyle)
{

  overRiddenStyle = aOverRiddenStyle;

  StepVisual_StyledItem::Init(aName, aStyles, aItem);
}

void StepVisual_OverRidingStyledItem::SetOverRiddenStyle(
  const occ::handle<StepVisual_StyledItem>& aOverRiddenStyle)
{
  overRiddenStyle = aOverRiddenStyle;
}

occ::handle<StepVisual_StyledItem> StepVisual_OverRidingStyledItem::OverRiddenStyle() const
{
  return overRiddenStyle;
}
