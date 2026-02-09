#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

class StepDimTol_LineProfileTolerance : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_LineProfileTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_LineProfileTolerance, StepDimTol_GeometricTolerance)
};
