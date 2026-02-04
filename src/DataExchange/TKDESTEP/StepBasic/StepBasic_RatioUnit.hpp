#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

class StepBasic_RatioUnit : public StepBasic_NamedUnit
{

public:
  //! Returns a RatioUnit
  Standard_EXPORT StepBasic_RatioUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_RatioUnit, StepBasic_NamedUnit)
};

