

#include <Standard_Type.hpp>
#include <StepBasic_ConversionBasedUnitAndTimeUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_TimeUnit.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndTimeUnit, StepBasic_ConversionBasedUnit)

StepBasic_ConversionBasedUnitAndTimeUnit::StepBasic_ConversionBasedUnitAndTimeUnit() = default;

void StepBasic_ConversionBasedUnitAndTimeUnit::Init(
  const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
  const occ::handle<TCollection_HAsciiString>&       aName,
  const occ::handle<Standard_Transient>&             aConversionFactor)
{

  StepBasic_ConversionBasedUnit::Init(aDimensions, aName, aConversionFactor);

  timeUnit = new StepBasic_TimeUnit();
  timeUnit->Init(aDimensions);
}

void StepBasic_ConversionBasedUnitAndTimeUnit::SetTimeUnit(
  const occ::handle<StepBasic_TimeUnit>& aTimeUnit)
{
  timeUnit = aTimeUnit;
}

occ::handle<StepBasic_TimeUnit> StepBasic_ConversionBasedUnitAndTimeUnit::TimeUnit() const
{
  return timeUnit;
}
