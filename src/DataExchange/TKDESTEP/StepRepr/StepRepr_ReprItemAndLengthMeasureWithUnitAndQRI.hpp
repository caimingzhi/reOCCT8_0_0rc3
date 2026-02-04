#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ReprItemAndMeasureWithUnitAndQRI.hpp>
class StepBasic_LengthMeasureWithUnit;

class StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI
    : public StepRepr_ReprItemAndMeasureWithUnitAndQRI
{

public:
  Standard_EXPORT StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI();

  Standard_EXPORT void SetLengthMeasureWithUnit(
    const occ::handle<StepBasic_LengthMeasureWithUnit>& aLMWU);

  Standard_EXPORT occ::handle<StepBasic_LengthMeasureWithUnit> GetLengthMeasureWithUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI,
                          StepRepr_ReprItemAndMeasureWithUnitAndQRI)

private:
  occ::handle<StepBasic_LengthMeasureWithUnit> myLengthMeasureWithUnit;
};
