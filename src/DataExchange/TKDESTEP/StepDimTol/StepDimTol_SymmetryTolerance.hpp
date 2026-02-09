#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

class StepDimTol_SymmetryTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  Standard_EXPORT StepDimTol_SymmetryTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_SymmetryTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};
