#pragma once

#include <Standard.hpp>

#include <StepRepr_PropertyDefinition.hpp>

class StepRepr_ProductDefinitionShape : public StepRepr_PropertyDefinition
{

public:
  Standard_EXPORT StepRepr_ProductDefinitionShape();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ProductDefinitionShape, StepRepr_PropertyDefinition)
};
