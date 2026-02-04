#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ReprItemAndMeasureWithUnitAndQRI.hpp>
class StepBasic_PlaneAngleMeasureWithUnit;

class StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI
    : public StepRepr_ReprItemAndMeasureWithUnitAndQRI
{

public:
  Standard_EXPORT StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI();

  Standard_EXPORT void SetPlaneAngleMeasureWithUnit(
    const occ::handle<StepBasic_PlaneAngleMeasureWithUnit>& aLMWU);

  Standard_EXPORT occ::handle<StepBasic_PlaneAngleMeasureWithUnit> GetPlaneAngleMeasureWithUnit()
    const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI,
                          StepRepr_ReprItemAndMeasureWithUnitAndQRI)

private:
  occ::handle<StepBasic_PlaneAngleMeasureWithUnit> myPlaneAngleMeasureWithUnit;
};
