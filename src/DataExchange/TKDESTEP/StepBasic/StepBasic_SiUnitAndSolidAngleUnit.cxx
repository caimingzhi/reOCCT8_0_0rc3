

#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_SiUnitAndSolidAngleUnit.hpp>
#include <StepBasic_SolidAngleUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SiUnitAndSolidAngleUnit, StepBasic_SiUnit)

StepBasic_SiUnitAndSolidAngleUnit::StepBasic_SiUnitAndSolidAngleUnit() = default;

void StepBasic_SiUnitAndSolidAngleUnit::Init(const bool                 hasAprefix,
                                             const StepBasic_SiPrefix   aPrefix,
                                             const StepBasic_SiUnitName aName)
{

  StepBasic_SiUnit::Init(hasAprefix, aPrefix, aName);

  solidAngleUnit = new StepBasic_SolidAngleUnit();
  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  aDimensions.Nullify();
  solidAngleUnit->Init(aDimensions);
}

void StepBasic_SiUnitAndSolidAngleUnit::SetSolidAngleUnit(
  const occ::handle<StepBasic_SolidAngleUnit>& aSolidAngleUnit)
{
  solidAngleUnit = aSolidAngleUnit;
}

occ::handle<StepBasic_SolidAngleUnit> StepBasic_SiUnitAndSolidAngleUnit::SolidAngleUnit() const
{
  return solidAngleUnit;
}
