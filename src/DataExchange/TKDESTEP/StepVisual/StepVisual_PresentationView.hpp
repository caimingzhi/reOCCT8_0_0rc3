#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_PresentationRepresentation.hpp>

class StepVisual_PresentationView : public StepVisual_PresentationRepresentation
{

public:
  Standard_EXPORT StepVisual_PresentationView();

  DEFINE_STANDARD_RTTIEXT(StepVisual_PresentationView, StepVisual_PresentationRepresentation)
};
