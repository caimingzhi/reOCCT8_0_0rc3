#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_DerivedShapeAspect.hpp>

class StepRepr_Tangent : public StepRepr_DerivedShapeAspect
{

public:
  Standard_EXPORT StepRepr_Tangent();

  DEFINE_STANDARD_RTTIEXT(StepRepr_Tangent, StepRepr_DerivedShapeAspect)
};
