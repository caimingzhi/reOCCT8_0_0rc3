#pragma once

#include <Standard.hpp>

#include <StepRepr_PropertyDefinitionRepresentation.hpp>

class StepShape_ShapeDefinitionRepresentation : public StepRepr_PropertyDefinitionRepresentation
{

public:
  Standard_EXPORT StepShape_ShapeDefinitionRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_ShapeDefinitionRepresentation,
                          StepRepr_PropertyDefinitionRepresentation)
};
