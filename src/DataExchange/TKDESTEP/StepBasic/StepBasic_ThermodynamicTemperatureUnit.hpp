#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

//! Representation of STEP entity ThermodynamicTemperatureUnit
class StepBasic_ThermodynamicTemperatureUnit : public StepBasic_NamedUnit
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ThermodynamicTemperatureUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_ThermodynamicTemperatureUnit, StepBasic_NamedUnit)
};

