#pragma once


#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

//! Representation of STEP entity StraightnessTolerance
class StepDimTol_StraightnessTolerance : public StepDimTol_GeometricTolerance
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_StraightnessTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_StraightnessTolerance, StepDimTol_GeometricTolerance)
};

