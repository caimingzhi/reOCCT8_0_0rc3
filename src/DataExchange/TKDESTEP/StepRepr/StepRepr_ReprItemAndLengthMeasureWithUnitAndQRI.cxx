

#include <Standard_Type.hpp>
#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI,
                           StepRepr_ReprItemAndMeasureWithUnitAndQRI)

StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI::StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI()

{
  myLengthMeasureWithUnit = new StepBasic_LengthMeasureWithUnit();
}

void StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI::SetLengthMeasureWithUnit(
  const occ::handle<StepBasic_LengthMeasureWithUnit>& aLMWU)
{
  myLengthMeasureWithUnit = aLMWU;
}

occ::handle<StepBasic_LengthMeasureWithUnit> StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI::
  GetLengthMeasureWithUnit() const
{
  return myLengthMeasureWithUnit;
}
