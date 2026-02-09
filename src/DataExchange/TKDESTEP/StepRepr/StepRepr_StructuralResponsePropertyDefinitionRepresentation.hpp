#pragma once

#include <Standard.hpp>

#include <StepRepr_PropertyDefinitionRepresentation.hpp>

class StepRepr_StructuralResponsePropertyDefinitionRepresentation
    : public StepRepr_PropertyDefinitionRepresentation
{

public:
  Standard_EXPORT StepRepr_StructuralResponsePropertyDefinitionRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepRepr_StructuralResponsePropertyDefinitionRepresentation,
                          StepRepr_PropertyDefinitionRepresentation)
};
