#pragma once

#include <Standard.hpp>

#include <StepVisual_AnnotationOccurrence.hpp>

class StepVisual_DraughtingAnnotationOccurrence : public StepVisual_AnnotationOccurrence
{

public:
  Standard_EXPORT StepVisual_DraughtingAnnotationOccurrence();

  DEFINE_STANDARD_RTTIEXT(StepVisual_DraughtingAnnotationOccurrence,
                          StepVisual_AnnotationOccurrence)
};
