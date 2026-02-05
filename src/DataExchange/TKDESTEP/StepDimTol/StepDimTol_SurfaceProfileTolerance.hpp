#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

//! Representation of STEP entity SurfaceProfileTolerance
class StepDimTol_SurfaceProfileTolerance : public StepDimTol_GeometricTolerance
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_SurfaceProfileTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_SurfaceProfileTolerance, StepDimTol_GeometricTolerance)
};
