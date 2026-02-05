#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

//! Representation of STEP entity TotalRunoutTolerance
class StepDimTol_TotalRunoutTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_TotalRunoutTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_TotalRunoutTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};
