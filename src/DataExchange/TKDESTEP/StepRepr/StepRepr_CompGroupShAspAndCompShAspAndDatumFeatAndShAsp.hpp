#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_CompShAspAndDatumFeatAndShAsp.hpp>

//! Added for Dimensional Tolerances
class StepRepr_CompGroupShAspAndCompShAspAndDatumFeatAndShAsp
    : public StepRepr_CompShAspAndDatumFeatAndShAsp
{

public:
  Standard_EXPORT StepRepr_CompGroupShAspAndCompShAspAndDatumFeatAndShAsp();

  DEFINE_STANDARD_RTTIEXT(StepRepr_CompGroupShAspAndCompShAspAndDatumFeatAndShAsp,
                          StepRepr_CompShAspAndDatumFeatAndShAsp)
};
