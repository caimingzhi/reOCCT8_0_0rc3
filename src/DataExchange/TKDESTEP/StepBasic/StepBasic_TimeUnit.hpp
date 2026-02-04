#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

class StepBasic_TimeUnit : public StepBasic_NamedUnit
{

public:
  //! Returns a TimeUnit
  Standard_EXPORT StepBasic_TimeUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_TimeUnit, StepBasic_NamedUnit)
};

