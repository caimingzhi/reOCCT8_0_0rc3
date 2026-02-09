

#include <Standard_Type.hpp>
#include <StepBasic_ConversionBasedUnitAndRatioUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_RatioUnit.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndRatioUnit, StepBasic_ConversionBasedUnit)

StepBasic_ConversionBasedUnitAndRatioUnit::StepBasic_ConversionBasedUnitAndRatioUnit() = default;

void StepBasic_ConversionBasedUnitAndRatioUnit::Init(
  const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
  const occ::handle<TCollection_HAsciiString>&       aName,
  const occ::handle<Standard_Transient>&             aConversionFactor)
{

  StepBasic_ConversionBasedUnit::Init(aDimensions, aName, aConversionFactor);

  ratioUnit = new StepBasic_RatioUnit();
  ratioUnit->Init(aDimensions);
}

void StepBasic_ConversionBasedUnitAndRatioUnit::SetRatioUnit(
  const occ::handle<StepBasic_RatioUnit>& aRatioUnit)
{
  ratioUnit = aRatioUnit;
}

occ::handle<StepBasic_RatioUnit> StepBasic_ConversionBasedUnitAndRatioUnit::RatioUnit() const
{
  return ratioUnit;
}
