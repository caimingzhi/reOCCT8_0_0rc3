#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ProductDefinitionContext.hpp>

//! class added to Schema AP214 around April 1996
class StepBasic_DesignContext : public StepBasic_ProductDefinitionContext
{

public:
  Standard_EXPORT StepBasic_DesignContext();

  DEFINE_STANDARD_RTTIEXT(StepBasic_DesignContext, StepBasic_ProductDefinitionContext)
};

