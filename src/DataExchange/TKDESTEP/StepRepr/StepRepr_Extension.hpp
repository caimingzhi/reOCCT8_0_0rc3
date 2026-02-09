#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_DerivedShapeAspect.hpp>

class StepRepr_Extension : public StepRepr_DerivedShapeAspect
{

public:
  Standard_EXPORT StepRepr_Extension();

  DEFINE_STANDARD_RTTIEXT(StepRepr_Extension, StepRepr_DerivedShapeAspect)
};
