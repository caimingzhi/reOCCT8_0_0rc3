#include <Standard_Type.hpp>
#include <StepBasic_PlaneAngleMeasureWithUnit.hpp>
#include <StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI,
                           StepRepr_ReprItemAndMeasureWithUnitAndQRI)

StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI::
  StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI()

{
  myPlaneAngleMeasureWithUnit = new StepBasic_PlaneAngleMeasureWithUnit();
}

void StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI::SetPlaneAngleMeasureWithUnit(
  const occ::handle<StepBasic_PlaneAngleMeasureWithUnit>& aLMWU)
{
  myPlaneAngleMeasureWithUnit = aLMWU;
}

occ::handle<StepBasic_PlaneAngleMeasureWithUnit>
  StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI::GetPlaneAngleMeasureWithUnit() const
{
  return myPlaneAngleMeasureWithUnit;
}
