#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspect.hpp>

//! Added for Dimensional Tolerances
class StepRepr_DerivedShapeAspect : public StepRepr_ShapeAspect
{

public:
  Standard_EXPORT StepRepr_DerivedShapeAspect();

  DEFINE_STANDARD_RTTIEXT(StepRepr_DerivedShapeAspect, StepRepr_ShapeAspect)
};
