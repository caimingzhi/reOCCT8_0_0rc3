#pragma once


#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

//! Representation of STEP entity ConcentricityTolerance
class StepDimTol_ConcentricityTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_ConcentricityTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_ConcentricityTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};

