#pragma once

#include <Standard.hpp>

#include <StepVisual_AreaOrView.hpp>
#include <StepVisual_Colour.hpp>

class StepVisual_BackgroundColour : public StepVisual_Colour
{

public:
  Standard_EXPORT StepVisual_BackgroundColour();

  Standard_EXPORT void Init(const StepVisual_AreaOrView& aPresentation);

  Standard_EXPORT void SetPresentation(const StepVisual_AreaOrView& aPresentation);

  Standard_EXPORT StepVisual_AreaOrView Presentation() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_BackgroundColour, StepVisual_Colour)

private:
  StepVisual_AreaOrView presentation;
};
