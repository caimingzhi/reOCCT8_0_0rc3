#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

class StepDimTol_PositionTolerance : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_PositionTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_PositionTolerance, StepDimTol_GeometricTolerance)
};
