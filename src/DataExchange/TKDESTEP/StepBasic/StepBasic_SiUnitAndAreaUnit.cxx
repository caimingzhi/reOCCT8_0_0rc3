#include <Standard_Type.hpp>
#include <StepBasic_AreaUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_SiUnitAndAreaUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SiUnitAndAreaUnit, StepBasic_SiUnit)

StepBasic_SiUnitAndAreaUnit::StepBasic_SiUnitAndAreaUnit() = default;

void StepBasic_SiUnitAndAreaUnit::SetAreaUnit(const occ::handle<StepBasic_AreaUnit>& anAreaUnit)
{
  areaUnit = anAreaUnit;
}

occ::handle<StepBasic_AreaUnit> StepBasic_SiUnitAndAreaUnit::AreaUnit() const
{
  return areaUnit;
}
