#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepDimTol_DatumTarget.hpp>

//! Representation of STEP entity PlacedDatumTargetFeature
class StepDimTol_PlacedDatumTargetFeature : public StepDimTol_DatumTarget
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_PlacedDatumTargetFeature();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_PlacedDatumTargetFeature, StepDimTol_DatumTarget)
};
