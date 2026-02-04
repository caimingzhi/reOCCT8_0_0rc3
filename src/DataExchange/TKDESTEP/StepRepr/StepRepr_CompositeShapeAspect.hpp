#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspect.hpp>

//! Added for Dimensional Tolerances
class StepRepr_CompositeShapeAspect : public StepRepr_ShapeAspect
{

public:
  Standard_EXPORT StepRepr_CompositeShapeAspect();

  DEFINE_STANDARD_RTTIEXT(StepRepr_CompositeShapeAspect, StepRepr_ShapeAspect)
};

