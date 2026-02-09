#pragma once

#include <Standard.hpp>

#include <StepRepr_MaterialPropertyRepresentation.hpp>

class StepFEA_FeaMaterialPropertyRepresentation : public StepRepr_MaterialPropertyRepresentation
{

public:
  Standard_EXPORT StepFEA_FeaMaterialPropertyRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaMaterialPropertyRepresentation,
                          StepRepr_MaterialPropertyRepresentation)
};
