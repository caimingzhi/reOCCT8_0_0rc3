#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

class StepDimTol_RoundnessTolerance : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_RoundnessTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_RoundnessTolerance, StepDimTol_GeometricTolerance)
};
