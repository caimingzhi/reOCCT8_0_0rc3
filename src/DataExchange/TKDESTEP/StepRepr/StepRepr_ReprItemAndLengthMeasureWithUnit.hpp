#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ReprItemAndMeasureWithUnit.hpp>
class StepBasic_LengthMeasureWithUnit;

class StepRepr_ReprItemAndLengthMeasureWithUnit : public StepRepr_ReprItemAndMeasureWithUnit
{

public:
  Standard_EXPORT StepRepr_ReprItemAndLengthMeasureWithUnit();

  Standard_EXPORT void SetLengthMeasureWithUnit(
    const occ::handle<StepBasic_LengthMeasureWithUnit>& aLMWU);

  Standard_EXPORT occ::handle<StepBasic_LengthMeasureWithUnit> GetLengthMeasureWithUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_ReprItemAndLengthMeasureWithUnit,
                          StepRepr_ReprItemAndMeasureWithUnit)

private:
  occ::handle<StepBasic_LengthMeasureWithUnit> myLengthMeasureWithUnit;
};
