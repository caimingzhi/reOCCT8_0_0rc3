#pragma once


#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

//! Representation of STEP entity RoundnessTolerance
class StepDimTol_RoundnessTolerance : public StepDimTol_GeometricTolerance
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_RoundnessTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_RoundnessTolerance, StepDimTol_GeometricTolerance)
};

