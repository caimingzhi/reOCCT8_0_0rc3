#pragma once

#include <Standard.hpp>

#include <StepRepr_PropertyDefinition.hpp>

class StepRepr_MaterialProperty : public StepRepr_PropertyDefinition
{

public:
  Standard_EXPORT StepRepr_MaterialProperty();

  DEFINE_STANDARD_RTTIEXT(StepRepr_MaterialProperty, StepRepr_PropertyDefinition)
};
