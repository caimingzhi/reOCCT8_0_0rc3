#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

class StepBasic_ThermodynamicTemperatureUnit : public StepBasic_NamedUnit
{

public:
  Standard_EXPORT StepBasic_ThermodynamicTemperatureUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_ThermodynamicTemperatureUnit, StepBasic_NamedUnit)
};
