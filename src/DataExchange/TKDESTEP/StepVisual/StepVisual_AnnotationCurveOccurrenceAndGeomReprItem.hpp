#pragma once


#include <Standard.hpp>

#include <StepVisual_AnnotationCurveOccurrence.hpp>

//! Added for Dimensional Tolerances
//! Complex STEP entity AnnotationCurveOccurrence & AnnotationOccurrence &
//! GeometricRepresentationItem & RepresentationItem & StyledItem
class StepVisual_AnnotationCurveOccurrenceAndGeomReprItem
    : public StepVisual_AnnotationCurveOccurrence
{

public:
  Standard_EXPORT StepVisual_AnnotationCurveOccurrenceAndGeomReprItem();

  DEFINE_STANDARD_RTTIEXT(StepVisual_AnnotationCurveOccurrenceAndGeomReprItem,
                          StepVisual_AnnotationCurveOccurrence)
};
