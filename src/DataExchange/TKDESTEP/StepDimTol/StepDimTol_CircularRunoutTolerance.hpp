#pragma once


#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

//! Representation of STEP entity CircularRunoutTolerance
class StepDimTol_CircularRunoutTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_CircularRunoutTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_CircularRunoutTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};

