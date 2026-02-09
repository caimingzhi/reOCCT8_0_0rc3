

#include <StepVisual_ContextDependentInvisibility.hpp>
#include <StepVisual_InvisibilityContext.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_ContextDependentInvisibility, StepVisual_Invisibility)

StepVisual_ContextDependentInvisibility::StepVisual_ContextDependentInvisibility() = default;

void StepVisual_ContextDependentInvisibility::Init(
  const occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>>& aInvisibleItems,
  const StepVisual_InvisibilityContext&                             aPresentationContext)
{

  presentationContext = aPresentationContext;

  StepVisual_Invisibility::Init(aInvisibleItems);
}

void StepVisual_ContextDependentInvisibility::SetPresentationContext(
  const StepVisual_InvisibilityContext& aPresentationContext)
{
  presentationContext = aPresentationContext;
}

StepVisual_InvisibilityContext StepVisual_ContextDependentInvisibility::PresentationContext() const
{
  return presentationContext;
}
