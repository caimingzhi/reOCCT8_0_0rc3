#pragma once

#include <Standard.hpp>

#include <StepRepr_PropertyDefinitionRepresentation.hpp>

//! Representation of STEP entity ShapeDefinitionRepresentation
class StepShape_ShapeDefinitionRepresentation : public StepRepr_PropertyDefinitionRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_ShapeDefinitionRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_ShapeDefinitionRepresentation,
                          StepRepr_PropertyDefinitionRepresentation)
};
