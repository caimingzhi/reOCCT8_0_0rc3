#pragma once

#include <Standard.hpp>

#include <StepDimTol_ToleranceZoneDefinition.hpp>

class StepDimTol_NonUniformZoneDefinition : public StepDimTol_ToleranceZoneDefinition
{

public:
  Standard_EXPORT StepDimTol_NonUniformZoneDefinition();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_NonUniformZoneDefinition, StepDimTol_ToleranceZoneDefinition)
};
