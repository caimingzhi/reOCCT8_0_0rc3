#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

//! Representation of STEP entity ParallelismTolerance
class StepDimTol_ParallelismTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_ParallelismTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_ParallelismTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};
