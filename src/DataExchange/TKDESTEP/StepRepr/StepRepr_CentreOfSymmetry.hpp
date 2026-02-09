#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_DerivedShapeAspect.hpp>

class StepRepr_CentreOfSymmetry : public StepRepr_DerivedShapeAspect
{

public:
  Standard_EXPORT StepRepr_CentreOfSymmetry();

  DEFINE_STANDARD_RTTIEXT(StepRepr_CentreOfSymmetry, StepRepr_DerivedShapeAspect)
};
