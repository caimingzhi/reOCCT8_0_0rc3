

#include <StepBasic_ConversionBasedUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnit, StepBasic_NamedUnit)

StepBasic_ConversionBasedUnit::StepBasic_ConversionBasedUnit() = default;

void StepBasic_ConversionBasedUnit::Init(
  const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
  const occ::handle<TCollection_HAsciiString>&       aName,
  const occ::handle<Standard_Transient>&             aConversionFactor)
{

  name             = aName;
  conversionFactor = aConversionFactor;

  StepBasic_NamedUnit::Init(aDimensions);
}

void StepBasic_ConversionBasedUnit::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_ConversionBasedUnit::Name() const
{
  return name;
}

void StepBasic_ConversionBasedUnit::SetConversionFactor(
  const occ::handle<Standard_Transient>& aConversionFactor)
{
  conversionFactor = aConversionFactor;
}

occ::handle<Standard_Transient> StepBasic_ConversionBasedUnit::ConversionFactor() const
{
  return conversionFactor;
}
