

#include <Standard_Type.hpp>
#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepRepr_ReprItemAndLengthMeasureWithUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ReprItemAndLengthMeasureWithUnit,
                           StepRepr_ReprItemAndMeasureWithUnit)

StepRepr_ReprItemAndLengthMeasureWithUnit::StepRepr_ReprItemAndLengthMeasureWithUnit()

{
  myLengthMeasureWithUnit = new StepBasic_LengthMeasureWithUnit();
}

void StepRepr_ReprItemAndLengthMeasureWithUnit::SetLengthMeasureWithUnit(
  const occ::handle<StepBasic_LengthMeasureWithUnit>& aLMWU)
{
  myLengthMeasureWithUnit = aLMWU;
}

occ::handle<StepBasic_LengthMeasureWithUnit> StepRepr_ReprItemAndLengthMeasureWithUnit::
  GetLengthMeasureWithUnit() const
{
  return myLengthMeasureWithUnit;
}
