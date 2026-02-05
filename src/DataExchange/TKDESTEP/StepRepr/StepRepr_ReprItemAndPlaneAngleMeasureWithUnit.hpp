#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ReprItemAndMeasureWithUnit.hpp>
class StepBasic_PlaneAngleMeasureWithUnit;

class StepRepr_ReprItemAndPlaneAngleMeasureWithUnit : public StepRepr_ReprItemAndMeasureWithUnit
{

public:
  Standard_EXPORT StepRepr_ReprItemAndPlaneAngleMeasureWithUnit();

  Standard_EXPORT void SetPlaneAngleMeasureWithUnit(
    const occ::handle<StepBasic_PlaneAngleMeasureWithUnit>& aLMWU);

  Standard_EXPORT occ::handle<StepBasic_PlaneAngleMeasureWithUnit> GetPlaneAngleMeasureWithUnit()
    const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_ReprItemAndPlaneAngleMeasureWithUnit,
                          StepRepr_ReprItemAndMeasureWithUnit)

private:
  occ::handle<StepBasic_PlaneAngleMeasureWithUnit> myPlaneAngleMeasureWithUnit;
};
