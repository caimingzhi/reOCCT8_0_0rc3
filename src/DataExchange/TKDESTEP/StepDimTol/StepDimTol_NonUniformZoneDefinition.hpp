#pragma once


#include <Standard.hpp>

#include <StepDimTol_ToleranceZoneDefinition.hpp>

//! Representation of STEP entity NonUniformZoneDefinition
class StepDimTol_NonUniformZoneDefinition : public StepDimTol_ToleranceZoneDefinition
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_NonUniformZoneDefinition();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_NonUniformZoneDefinition, StepDimTol_ToleranceZoneDefinition)
};
