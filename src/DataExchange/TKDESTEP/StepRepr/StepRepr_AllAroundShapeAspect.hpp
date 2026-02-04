#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ContinuosShapeAspect.hpp>

//! Added for Dimensional Tolerances
class StepRepr_AllAroundShapeAspect : public StepRepr_ContinuosShapeAspect
{

public:
  Standard_EXPORT StepRepr_AllAroundShapeAspect();

  DEFINE_STANDARD_RTTIEXT(StepRepr_AllAroundShapeAspect, StepRepr_ContinuosShapeAspect)
};
