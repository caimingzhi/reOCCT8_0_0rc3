#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepRepr_DerivedShapeAspect.hpp>

class StepRepr_GeometricAlignment : public StepRepr_DerivedShapeAspect
{

public:
  Standard_EXPORT StepRepr_GeometricAlignment();

  DEFINE_STANDARD_RTTIEXT(StepRepr_GeometricAlignment, StepRepr_DerivedShapeAspect)
};
