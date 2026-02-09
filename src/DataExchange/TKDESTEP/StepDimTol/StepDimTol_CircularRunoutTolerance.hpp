#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

class StepDimTol_CircularRunoutTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  Standard_EXPORT StepDimTol_CircularRunoutTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_CircularRunoutTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};
