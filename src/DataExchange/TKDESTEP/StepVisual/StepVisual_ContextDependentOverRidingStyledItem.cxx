

#include <StepVisual_ContextDependentOverRidingStyledItem.hpp>
#include <StepVisual_StyleContextSelect.hpp>
#include <StepVisual_StyledItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_ContextDependentOverRidingStyledItem,
                           StepVisual_OverRidingStyledItem)

StepVisual_ContextDependentOverRidingStyledItem::StepVisual_ContextDependentOverRidingStyledItem() =
  default;

void StepVisual_ContextDependentOverRidingStyledItem::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                                                         aStyles,
  const occ::handle<Standard_Transient>&                                 aItem,
  const occ::handle<StepVisual_StyledItem>&                              aOverRiddenStyle,
  const occ::handle<NCollection_HArray1<StepVisual_StyleContextSelect>>& aStyleContext)
{

  styleContext = aStyleContext;

  StepVisual_OverRidingStyledItem::Init(aName, aStyles, aItem, aOverRiddenStyle);
}

void StepVisual_ContextDependentOverRidingStyledItem::SetStyleContext(
  const occ::handle<NCollection_HArray1<StepVisual_StyleContextSelect>>& aStyleContext)
{
  styleContext = aStyleContext;
}

occ::handle<NCollection_HArray1<StepVisual_StyleContextSelect>>
  StepVisual_ContextDependentOverRidingStyledItem::StyleContext() const
{
  return styleContext;
}

StepVisual_StyleContextSelect StepVisual_ContextDependentOverRidingStyledItem::StyleContextValue(
  const int num) const
{
  return styleContext->Value(num);
}

int StepVisual_ContextDependentOverRidingStyledItem::NbStyleContext() const
{
  return styleContext->Length();
}
