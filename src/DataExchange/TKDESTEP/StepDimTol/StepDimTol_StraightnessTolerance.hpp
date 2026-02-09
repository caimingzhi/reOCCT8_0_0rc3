#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

class StepDimTol_StraightnessTolerance : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_StraightnessTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_StraightnessTolerance, StepDimTol_GeometricTolerance)
};
