#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

class StepBasic_LengthUnit : public StepBasic_NamedUnit
{

public:
  Standard_EXPORT StepBasic_LengthUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_LengthUnit, StepBasic_NamedUnit)
};
