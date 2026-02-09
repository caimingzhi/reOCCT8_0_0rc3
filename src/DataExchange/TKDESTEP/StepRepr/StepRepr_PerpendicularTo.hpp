#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepRepr_DerivedShapeAspect.hpp>

class StepRepr_PerpendicularTo : public StepRepr_DerivedShapeAspect
{

public:
  Standard_EXPORT StepRepr_PerpendicularTo();

  DEFINE_STANDARD_RTTIEXT(StepRepr_PerpendicularTo, StepRepr_DerivedShapeAspect)
};
