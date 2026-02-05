#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

//! Representation of STEP entity CylindricityTolerance
class StepDimTol_CylindricityTolerance : public StepDimTol_GeometricTolerance
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_CylindricityTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_CylindricityTolerance, StepDimTol_GeometricTolerance)
};
