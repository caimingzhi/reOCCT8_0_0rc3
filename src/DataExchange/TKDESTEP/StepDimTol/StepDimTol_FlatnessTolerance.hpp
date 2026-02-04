#pragma once


#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

//! Representation of STEP entity FlatnessTolerance
class StepDimTol_FlatnessTolerance : public StepDimTol_GeometricTolerance
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_FlatnessTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_FlatnessTolerance, StepDimTol_GeometricTolerance)
};

