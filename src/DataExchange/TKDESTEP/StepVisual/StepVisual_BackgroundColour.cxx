

#include <StepVisual_BackgroundColour.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_BackgroundColour, StepVisual_Colour)

StepVisual_BackgroundColour::StepVisual_BackgroundColour() = default;

void StepVisual_BackgroundColour::Init(const StepVisual_AreaOrView& aPresentation)
{

  presentation = aPresentation;
}

void StepVisual_BackgroundColour::SetPresentation(const StepVisual_AreaOrView& aPresentation)
{
  presentation = aPresentation;
}

StepVisual_AreaOrView StepVisual_BackgroundColour::Presentation() const
{
  return presentation;
}
