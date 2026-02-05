#include <Standard_Type.hpp>
#include <StepBasic_PlaneAngleMeasureWithUnit.hpp>
#include <StepRepr_ReprItemAndPlaneAngleMeasureWithUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ReprItemAndPlaneAngleMeasureWithUnit,
                           StepRepr_ReprItemAndMeasureWithUnit)

//=================================================================================================

StepRepr_ReprItemAndPlaneAngleMeasureWithUnit::StepRepr_ReprItemAndPlaneAngleMeasureWithUnit()

{
  myPlaneAngleMeasureWithUnit = new StepBasic_PlaneAngleMeasureWithUnit();
}

//=================================================================================================

void StepRepr_ReprItemAndPlaneAngleMeasureWithUnit::SetPlaneAngleMeasureWithUnit(
  const occ::handle<StepBasic_PlaneAngleMeasureWithUnit>& aLMWU)
{
  myPlaneAngleMeasureWithUnit = aLMWU;
}

//=================================================================================================

occ::handle<StepBasic_PlaneAngleMeasureWithUnit> StepRepr_ReprItemAndPlaneAngleMeasureWithUnit::
  GetPlaneAngleMeasureWithUnit() const
{
  return myPlaneAngleMeasureWithUnit;
}
