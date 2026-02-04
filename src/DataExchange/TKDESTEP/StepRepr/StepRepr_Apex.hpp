#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_DerivedShapeAspect.hpp>

//! Added for Dimensional Tolerances
class StepRepr_Apex : public StepRepr_DerivedShapeAspect
{

public:
  Standard_EXPORT StepRepr_Apex();

  DEFINE_STANDARD_RTTIEXT(StepRepr_Apex, StepRepr_DerivedShapeAspect)
};
