#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

class StepDimTol_CylindricityTolerance : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_CylindricityTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_CylindricityTolerance, StepDimTol_GeometricTolerance)
};
