

#include <Standard_Type.hpp>
#include <StepBasic_ConversionBasedUnitAndMassUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MassUnit.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndMassUnit, StepBasic_ConversionBasedUnit)

StepBasic_ConversionBasedUnitAndMassUnit::StepBasic_ConversionBasedUnitAndMassUnit() = default;

void StepBasic_ConversionBasedUnitAndMassUnit::Init(
  const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
  const occ::handle<TCollection_HAsciiString>&       aName,
  const occ::handle<Standard_Transient>&             aConversionFactor)
{

  StepBasic_ConversionBasedUnit::Init(aDimensions, aName, aConversionFactor);

  massUnit = new StepBasic_MassUnit();
  massUnit->Init(aDimensions);
}

void StepBasic_ConversionBasedUnitAndMassUnit::SetMassUnit(
  const occ::handle<StepBasic_MassUnit>& aMassUnit)
{
  massUnit = aMassUnit;
}

occ::handle<StepBasic_MassUnit> StepBasic_ConversionBasedUnitAndMassUnit::MassUnit() const
{
  return massUnit;
}
