#pragma once


#include <Standard.hpp>

#include <StepRepr_PropertyDefinition.hpp>

//! Representation of STEP entity ProductDefinitionShape
class StepRepr_ProductDefinitionShape : public StepRepr_PropertyDefinition
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_ProductDefinitionShape();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ProductDefinitionShape, StepRepr_PropertyDefinition)
};

