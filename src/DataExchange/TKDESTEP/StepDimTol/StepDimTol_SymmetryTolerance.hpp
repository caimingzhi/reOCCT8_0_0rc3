#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

//! Representation of STEP entity SymmetryTolerance
class StepDimTol_SymmetryTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_SymmetryTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_SymmetryTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};
