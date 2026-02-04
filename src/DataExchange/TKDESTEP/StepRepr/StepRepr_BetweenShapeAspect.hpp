#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ContinuosShapeAspect.hpp>

//! Added for Dimensional Tolerances
class StepRepr_BetweenShapeAspect : public StepRepr_ContinuosShapeAspect
{

public:
  Standard_EXPORT StepRepr_BetweenShapeAspect();

  DEFINE_STANDARD_RTTIEXT(StepRepr_BetweenShapeAspect, StepRepr_ContinuosShapeAspect)
};
