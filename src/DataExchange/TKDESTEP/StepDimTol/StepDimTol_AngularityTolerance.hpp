#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

class StepDimTol_AngularityTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  Standard_EXPORT StepDimTol_AngularityTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_AngularityTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};
