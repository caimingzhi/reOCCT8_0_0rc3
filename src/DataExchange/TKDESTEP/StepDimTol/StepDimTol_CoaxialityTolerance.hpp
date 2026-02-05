#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

//! Representation of STEP entity CoaxialityTolerance
class StepDimTol_CoaxialityTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_CoaxialityTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_CoaxialityTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};
