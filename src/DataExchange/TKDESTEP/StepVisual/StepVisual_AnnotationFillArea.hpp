#pragma once


#include <Standard.hpp>

#include <StepShape_GeometricCurveSet.hpp>
#include <Standard_Integer.hpp>

class StepVisual_AnnotationFillArea : public StepShape_GeometricCurveSet
{

public:
  //! Returns a AnnotationFillArea
  Standard_EXPORT StepVisual_AnnotationFillArea();

  DEFINE_STANDARD_RTTIEXT(StepVisual_AnnotationFillArea, StepShape_GeometricCurveSet)
};
