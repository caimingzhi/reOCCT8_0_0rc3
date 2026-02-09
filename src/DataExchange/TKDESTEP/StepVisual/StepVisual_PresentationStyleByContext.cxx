

#include <StepVisual_PresentationStyleByContext.hpp>
#include <StepVisual_StyleContextSelect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PresentationStyleByContext,
                           StepVisual_PresentationStyleAssignment)

StepVisual_PresentationStyleByContext::StepVisual_PresentationStyleByContext() = default;

void StepVisual_PresentationStyleByContext::Init(
  const occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>>& aStyles,
  const StepVisual_StyleContextSelect&                                        aStyleContext)
{

  styleContext = aStyleContext;

  StepVisual_PresentationStyleAssignment::Init(aStyles);
}

void StepVisual_PresentationStyleByContext::SetStyleContext(
  const StepVisual_StyleContextSelect& aStyleContext)
{
  styleContext = aStyleContext;
}

StepVisual_StyleContextSelect StepVisual_PresentationStyleByContext::StyleContext() const
{
  return styleContext;
}
