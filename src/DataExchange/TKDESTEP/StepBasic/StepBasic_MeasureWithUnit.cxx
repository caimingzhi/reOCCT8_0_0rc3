

#include <Standard_Type.hpp>
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_Unit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_MeasureWithUnit, Standard_Transient)

StepBasic_MeasureWithUnit::StepBasic_MeasureWithUnit() = default;

void StepBasic_MeasureWithUnit::Init(
  const occ::handle<StepBasic_MeasureValueMember>& aValueComponent,
  const StepBasic_Unit&                            aUnitComponent)
{

  valueComponent = aValueComponent;
  unitComponent  = aUnitComponent;
}

void StepBasic_MeasureWithUnit::SetValueComponent(const double aValueComponent)
{
  if (valueComponent.IsNull())
    valueComponent = new StepBasic_MeasureValueMember;
  valueComponent->SetReal(aValueComponent);
}

double StepBasic_MeasureWithUnit::ValueComponent() const
{
  return (valueComponent.IsNull() ? 0.0 : valueComponent->Real());
}

occ::handle<StepBasic_MeasureValueMember> StepBasic_MeasureWithUnit::ValueComponentMember() const
{
  return valueComponent;
}

void StepBasic_MeasureWithUnit::SetValueComponentMember(
  const occ::handle<StepBasic_MeasureValueMember>& val)
{
  valueComponent = val;
}

void StepBasic_MeasureWithUnit::SetUnitComponent(const StepBasic_Unit& aUnitComponent)
{
  unitComponent = aUnitComponent;
}

StepBasic_Unit StepBasic_MeasureWithUnit::UnitComponent() const
{
  return unitComponent;
}
