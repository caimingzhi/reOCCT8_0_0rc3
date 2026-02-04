#pragma once


#include <Standard.hpp>

#include <StepRepr_MaterialPropertyRepresentation.hpp>

//! Representation of STEP entity FeaMaterialPropertyRepresentation
class StepFEA_FeaMaterialPropertyRepresentation : public StepRepr_MaterialPropertyRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaMaterialPropertyRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaMaterialPropertyRepresentation,
                          StepRepr_MaterialPropertyRepresentation)
};

