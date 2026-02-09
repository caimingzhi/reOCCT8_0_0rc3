#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

class StepBasic_SolidAngleUnit : public StepBasic_NamedUnit
{

public:
  Standard_EXPORT StepBasic_SolidAngleUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_SolidAngleUnit, StepBasic_NamedUnit)
};
