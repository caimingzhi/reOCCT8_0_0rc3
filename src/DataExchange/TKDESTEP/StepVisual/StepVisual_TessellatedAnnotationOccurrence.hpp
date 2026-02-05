#pragma once

#include <Standard.hpp>

#include <StepVisual_StyledItem.hpp>

class StepVisual_TessellatedAnnotationOccurrence : public StepVisual_StyledItem
{
public:
  //! Returns a TesselatedAnnotationOccurence
  Standard_EXPORT StepVisual_TessellatedAnnotationOccurrence();

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedAnnotationOccurrence, StepVisual_StyledItem)
};
