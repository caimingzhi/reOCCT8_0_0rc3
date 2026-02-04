#pragma once


#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

//! Representation of STEP entity PerpendicularityTolerance
class StepDimTol_PerpendicularityTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_PerpendicularityTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_PerpendicularityTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};

