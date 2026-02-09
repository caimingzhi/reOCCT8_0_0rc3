

#include <Standard_Type.hpp>
#include <StepBasic_ConversionBasedUnitAndSolidAngleUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_SolidAngleUnit.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndSolidAngleUnit,
                           StepBasic_ConversionBasedUnit)

StepBasic_ConversionBasedUnitAndSolidAngleUnit::StepBasic_ConversionBasedUnitAndSolidAngleUnit() =
  default;

void StepBasic_ConversionBasedUnitAndSolidAngleUnit::Init(
  const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
  const occ::handle<TCollection_HAsciiString>&       aName,
  const occ::handle<Standard_Transient>&             aConversionFactor)
{

  StepBasic_ConversionBasedUnit::Init(aDimensions, aName, aConversionFactor);

  solidAngleUnit = new StepBasic_SolidAngleUnit();
  solidAngleUnit->Init(aDimensions);
}

void StepBasic_ConversionBasedUnitAndSolidAngleUnit::SetSolidAngleUnit(
  const occ::handle<StepBasic_SolidAngleUnit>& aSolidAngleUnit)
{
  solidAngleUnit = aSolidAngleUnit;
}

occ::handle<StepBasic_SolidAngleUnit> StepBasic_ConversionBasedUnitAndSolidAngleUnit::
  SolidAngleUnit() const
{
  return solidAngleUnit;
}
