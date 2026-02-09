#pragma once

#include <Standard.hpp>

#include <StepRepr_PropertyDefinition.hpp>

class StepRepr_StructuralResponseProperty : public StepRepr_PropertyDefinition
{

public:
  Standard_EXPORT StepRepr_StructuralResponseProperty();

  DEFINE_STANDARD_RTTIEXT(StepRepr_StructuralResponseProperty, StepRepr_PropertyDefinition)
};
