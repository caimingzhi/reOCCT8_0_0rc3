#pragma once

#include <Standard.hpp>

#include <StepRepr_PropertyDefinitionRepresentation.hpp>

//! Representation of STEP entity StructuralResponsePropertyDefinitionRepresentation
class StepRepr_StructuralResponsePropertyDefinitionRepresentation
    : public StepRepr_PropertyDefinitionRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_StructuralResponsePropertyDefinitionRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepRepr_StructuralResponsePropertyDefinitionRepresentation,
                          StepRepr_PropertyDefinitionRepresentation)
};
