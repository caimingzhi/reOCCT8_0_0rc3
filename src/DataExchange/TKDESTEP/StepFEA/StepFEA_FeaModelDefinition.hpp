#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspect.hpp>

//! Representation of STEP entity FeaModelDefinition
class StepFEA_FeaModelDefinition : public StepRepr_ShapeAspect
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaModelDefinition();

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaModelDefinition, StepRepr_ShapeAspect)
};

