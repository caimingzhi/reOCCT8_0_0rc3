#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ProductContext.hpp>

class StepBasic_MechanicalContext : public StepBasic_ProductContext
{

public:
  //! Returns a MechanicalContext
  Standard_EXPORT StepBasic_MechanicalContext();

  DEFINE_STANDARD_RTTIEXT(StepBasic_MechanicalContext, StepBasic_ProductContext)
};
