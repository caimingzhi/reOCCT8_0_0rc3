#pragma once

#include <Standard.hpp>

#include <StepVisual_AnnotationCurveOccurrence.hpp>

class StepVisual_AnnotationCurveOccurrenceAndGeomReprItem
    : public StepVisual_AnnotationCurveOccurrence
{

public:
  Standard_EXPORT StepVisual_AnnotationCurveOccurrenceAndGeomReprItem();

  DEFINE_STANDARD_RTTIEXT(StepVisual_AnnotationCurveOccurrenceAndGeomReprItem,
                          StepVisual_AnnotationCurveOccurrence)
};
