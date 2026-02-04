#pragma once


#include <Standard.hpp>

#include <StepVisual_AnnotationOccurrence.hpp>

class StepVisual_AnnotationCurveOccurrence : public StepVisual_AnnotationOccurrence
{
public:
  //! Returns a AnnotationCurveOccurrence
  Standard_EXPORT StepVisual_AnnotationCurveOccurrence();

  DEFINE_STANDARD_RTTIEXT(StepVisual_AnnotationCurveOccurrence, StepVisual_AnnotationOccurrence)
};
