#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationContext.hpp>

class StepRepr_ParametricRepresentationContext : public StepRepr_RepresentationContext
{

public:
  Standard_EXPORT StepRepr_ParametricRepresentationContext();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ParametricRepresentationContext, StepRepr_RepresentationContext)
};
