#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspect.hpp>

//! Representation of STEP entity NodeDefinition
class StepFEA_NodeDefinition : public StepRepr_ShapeAspect
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_NodeDefinition();

  DEFINE_STANDARD_RTTIEXT(StepFEA_NodeDefinition, StepRepr_ShapeAspect)
};

