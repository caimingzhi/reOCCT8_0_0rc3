

#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_UncertaintyMeasureWithUnit.hpp>
#include <StepBasic_Unit.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_UncertaintyMeasureWithUnit, StepBasic_MeasureWithUnit)

StepBasic_UncertaintyMeasureWithUnit::StepBasic_UncertaintyMeasureWithUnit() = default;

void StepBasic_UncertaintyMeasureWithUnit::Init(
  const occ::handle<StepBasic_MeasureValueMember>& aValueComponent,
  const StepBasic_Unit&                            aUnitComponent,
  const occ::handle<TCollection_HAsciiString>&     aName,
  const occ::handle<TCollection_HAsciiString>&     aDescription)
{

  name        = aName;
  description = aDescription;

  StepBasic_MeasureWithUnit::Init(aValueComponent, aUnitComponent);
}

void StepBasic_UncertaintyMeasureWithUnit::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_UncertaintyMeasureWithUnit::Name() const
{
  return name;
}

void StepBasic_UncertaintyMeasureWithUnit::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepBasic_UncertaintyMeasureWithUnit::Description() const
{
  return description;
}
