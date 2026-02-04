#pragma once


#include <Standard.hpp>

#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>

//! Representation of STEP entity AngularityTolerance
class StepDimTol_AngularityTolerance : public StepDimTol_GeometricToleranceWithDatumReference
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_AngularityTolerance();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_AngularityTolerance,
                          StepDimTol_GeometricToleranceWithDatumReference)
};

