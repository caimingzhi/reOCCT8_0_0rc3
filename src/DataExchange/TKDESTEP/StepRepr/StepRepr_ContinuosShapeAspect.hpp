#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_CompositeShapeAspect.hpp>

class StepRepr_ContinuosShapeAspect : public StepRepr_CompositeShapeAspect
{

public:
  Standard_EXPORT StepRepr_ContinuosShapeAspect();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ContinuosShapeAspect, StepRepr_CompositeShapeAspect)
};
