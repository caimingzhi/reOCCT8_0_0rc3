#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepDimTol_DatumTarget.hpp>

class StepDimTol_PlacedDatumTargetFeature : public StepDimTol_DatumTarget
{

public:
  Standard_EXPORT StepDimTol_PlacedDatumTargetFeature();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_PlacedDatumTargetFeature, StepDimTol_DatumTarget)
};
