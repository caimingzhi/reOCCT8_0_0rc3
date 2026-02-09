#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspect.hpp>

class StepFEA_FeaModelDefinition : public StepRepr_ShapeAspect
{

public:
  Standard_EXPORT StepFEA_FeaModelDefinition();

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaModelDefinition, StepRepr_ShapeAspect)
};
