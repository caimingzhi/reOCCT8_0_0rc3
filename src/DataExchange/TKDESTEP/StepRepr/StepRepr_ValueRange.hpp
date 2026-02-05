#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_CompoundRepresentationItem.hpp>

//! Added for Dimensional Tolerances
class StepRepr_ValueRange : public StepRepr_CompoundRepresentationItem
{

public:
  Standard_EXPORT StepRepr_ValueRange();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ValueRange, StepRepr_CompoundRepresentationItem)
};
