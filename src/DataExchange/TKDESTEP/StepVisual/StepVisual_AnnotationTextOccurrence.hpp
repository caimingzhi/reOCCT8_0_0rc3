#pragma once


#include <Standard.hpp>

#include <StepVisual_AnnotationOccurrence.hpp>

class StepVisual_AnnotationTextOccurrence : public StepVisual_AnnotationOccurrence
{

public:
  //! Returns a AnnotationTextOccurrence
  Standard_EXPORT StepVisual_AnnotationTextOccurrence();

  DEFINE_STANDARD_RTTIEXT(StepVisual_AnnotationTextOccurrence, StepVisual_AnnotationOccurrence)
};

