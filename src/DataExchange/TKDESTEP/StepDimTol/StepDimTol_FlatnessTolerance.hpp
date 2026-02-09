#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

class StepDimTol_FlatnessTolerance : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_FlatnessTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_FlatnessTolerance, StepDimTol_GeometricTolerance)
};
