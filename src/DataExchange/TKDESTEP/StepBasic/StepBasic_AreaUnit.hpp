#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

class StepBasic_AreaUnit : public StepBasic_NamedUnit
{

public:
  Standard_EXPORT StepBasic_AreaUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_AreaUnit, StepBasic_NamedUnit)
};
