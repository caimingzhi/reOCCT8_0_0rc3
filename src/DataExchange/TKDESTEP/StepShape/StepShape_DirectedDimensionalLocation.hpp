#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_DimensionalLocation.hpp>

//! Representation of STEP entity DirectedDimensionalLocation
class StepShape_DirectedDimensionalLocation : public StepShape_DimensionalLocation
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_DirectedDimensionalLocation();

  DEFINE_STANDARD_RTTIEXT(StepShape_DirectedDimensionalLocation, StepShape_DimensionalLocation)
};
