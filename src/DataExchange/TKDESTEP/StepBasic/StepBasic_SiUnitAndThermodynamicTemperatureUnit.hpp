#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_SiUnit.hpp>
#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitName.hpp>
class StepBasic_ThermodynamicTemperatureUnit;

class StepBasic_SiUnitAndThermodynamicTemperatureUnit : public StepBasic_SiUnit
{

public:
  //! Returns a SiUnitAndThermodynamicTemperatureUnit
  Standard_EXPORT StepBasic_SiUnitAndThermodynamicTemperatureUnit();

  Standard_EXPORT void Init(const bool                 hasAprefix,
                            const StepBasic_SiPrefix   aPrefix,
                            const StepBasic_SiUnitName aName);

  Standard_EXPORT void SetThermodynamicTemperatureUnit(
    const occ::handle<StepBasic_ThermodynamicTemperatureUnit>& aThermodynamicTemperatureUnit);

  Standard_EXPORT occ::handle<StepBasic_ThermodynamicTemperatureUnit> ThermodynamicTemperatureUnit()
    const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SiUnitAndThermodynamicTemperatureUnit, StepBasic_SiUnit)

private:
  occ::handle<StepBasic_ThermodynamicTemperatureUnit> thermodynamicTemperatureUnit;
};
