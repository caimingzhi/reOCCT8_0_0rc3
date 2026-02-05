#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_CompositeShapeAspect.hpp>

//! Added for Dimensional Tolerances
class StepRepr_CompositeGroupShapeAspect : public StepRepr_CompositeShapeAspect
{

public:
  Standard_EXPORT StepRepr_CompositeGroupShapeAspect();

  DEFINE_STANDARD_RTTIEXT(StepRepr_CompositeGroupShapeAspect, StepRepr_CompositeShapeAspect)
};
