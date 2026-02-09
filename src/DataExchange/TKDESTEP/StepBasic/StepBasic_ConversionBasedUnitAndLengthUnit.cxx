

#include <Standard_Type.hpp>
#include <StepBasic_ConversionBasedUnitAndLengthUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_LengthUnit.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndLengthUnit,
                           StepBasic_ConversionBasedUnit)

StepBasic_ConversionBasedUnitAndLengthUnit::StepBasic_ConversionBasedUnitAndLengthUnit() = default;

void StepBasic_ConversionBasedUnitAndLengthUnit::Init(
  const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
  const occ::handle<TCollection_HAsciiString>&       aName,
  const occ::handle<Standard_Transient>&             aConversionFactor)
{

  StepBasic_ConversionBasedUnit::Init(aDimensions, aName, aConversionFactor);

  lengthUnit = new StepBasic_LengthUnit();
  lengthUnit->Init(aDimensions);
}

void StepBasic_ConversionBasedUnitAndLengthUnit::SetLengthUnit(
  const occ::handle<StepBasic_LengthUnit>& aLengthUnit)
{
  lengthUnit = aLengthUnit;
}

occ::handle<StepBasic_LengthUnit> StepBasic_ConversionBasedUnitAndLengthUnit::LengthUnit() const
{
  return lengthUnit;
}
