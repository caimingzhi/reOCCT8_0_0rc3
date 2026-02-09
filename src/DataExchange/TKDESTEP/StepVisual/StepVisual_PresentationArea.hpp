#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_PresentationRepresentation.hpp>

class StepVisual_PresentationArea : public StepVisual_PresentationRepresentation
{

public:
  Standard_EXPORT StepVisual_PresentationArea();

  DEFINE_STANDARD_RTTIEXT(StepVisual_PresentationArea, StepVisual_PresentationRepresentation)
};
