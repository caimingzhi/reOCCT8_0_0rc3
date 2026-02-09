

#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_SiUnitAndThermodynamicTemperatureUnit.hpp>
#include <StepBasic_ThermodynamicTemperatureUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SiUnitAndThermodynamicTemperatureUnit, StepBasic_SiUnit)

StepBasic_SiUnitAndThermodynamicTemperatureUnit::StepBasic_SiUnitAndThermodynamicTemperatureUnit() =
  default;

void StepBasic_SiUnitAndThermodynamicTemperatureUnit::Init(const bool                 hasAprefix,
                                                           const StepBasic_SiPrefix   aPrefix,
                                                           const StepBasic_SiUnitName aName)
{

  StepBasic_SiUnit::Init(hasAprefix, aPrefix, aName);

  thermodynamicTemperatureUnit = new StepBasic_ThermodynamicTemperatureUnit();
  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  aDimensions.Nullify();
  thermodynamicTemperatureUnit->Init(aDimensions);
}

void StepBasic_SiUnitAndThermodynamicTemperatureUnit::SetThermodynamicTemperatureUnit(
  const occ::handle<StepBasic_ThermodynamicTemperatureUnit>& aThermodynamicTemperatureUnit)
{
  thermodynamicTemperatureUnit = aThermodynamicTemperatureUnit;
}

occ::handle<StepBasic_ThermodynamicTemperatureUnit>
  StepBasic_SiUnitAndThermodynamicTemperatureUnit::ThermodynamicTemperatureUnit() const
{
  return thermodynamicTemperatureUnit;
}
