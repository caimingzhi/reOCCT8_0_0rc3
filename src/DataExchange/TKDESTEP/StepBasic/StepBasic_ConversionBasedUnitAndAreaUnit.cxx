#include <Standard_Type.hpp>
#include <StepBasic_AreaUnit.hpp>
#include <StepBasic_ConversionBasedUnitAndAreaUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndAreaUnit, StepBasic_ConversionBasedUnit)

StepBasic_ConversionBasedUnitAndAreaUnit::StepBasic_ConversionBasedUnitAndAreaUnit() = default;

void StepBasic_ConversionBasedUnitAndAreaUnit::SetAreaUnit(
  const occ::handle<StepBasic_AreaUnit>& anAreaUnit)
{
  areaUnit = anAreaUnit;
}

occ::handle<StepBasic_AreaUnit> StepBasic_ConversionBasedUnitAndAreaUnit::AreaUnit() const
{
  return areaUnit;
}
