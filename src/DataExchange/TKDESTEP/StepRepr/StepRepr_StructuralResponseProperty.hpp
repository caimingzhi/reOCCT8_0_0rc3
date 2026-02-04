#pragma once


#include <Standard.hpp>

#include <StepRepr_PropertyDefinition.hpp>

//! Representation of STEP entity StructuralResponseProperty
class StepRepr_StructuralResponseProperty : public StepRepr_PropertyDefinition
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_StructuralResponseProperty();

  DEFINE_STANDARD_RTTIEXT(StepRepr_StructuralResponseProperty, StepRepr_PropertyDefinition)
};

