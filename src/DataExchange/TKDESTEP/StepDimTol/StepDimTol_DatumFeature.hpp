#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspect.hpp>

//! Representation of STEP entity DatumFeature
class StepDimTol_DatumFeature : public StepRepr_ShapeAspect
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_DatumFeature();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_DatumFeature, StepRepr_ShapeAspect)
};
