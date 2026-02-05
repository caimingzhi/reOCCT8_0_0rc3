#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspectRelationship.hpp>

//! Representation of STEP entity DimensionalLocation
class StepShape_DimensionalLocation : public StepRepr_ShapeAspectRelationship
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_DimensionalLocation();

  DEFINE_STANDARD_RTTIEXT(StepShape_DimensionalLocation, StepRepr_ShapeAspectRelationship)
};
