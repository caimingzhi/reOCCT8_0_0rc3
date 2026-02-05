#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

//! Representation of STEP entity LineProfileTolerance
class StepDimTol_LineProfileTolerance : public StepDimTol_GeometricTolerance
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_LineProfileTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_LineProfileTolerance, StepDimTol_GeometricTolerance)
};
