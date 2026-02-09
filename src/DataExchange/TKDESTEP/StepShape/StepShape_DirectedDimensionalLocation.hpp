#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_DimensionalLocation.hpp>

class StepShape_DirectedDimensionalLocation : public StepShape_DimensionalLocation
{

public:
  Standard_EXPORT StepShape_DirectedDimensionalLocation();

  DEFINE_STANDARD_RTTIEXT(StepShape_DirectedDimensionalLocation, StepShape_DimensionalLocation)
};
