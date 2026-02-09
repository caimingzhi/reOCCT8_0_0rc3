#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

class StepDimTol_CoaxialityTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  Standard_EXPORT StepDimTol_CoaxialityTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_CoaxialityTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};
