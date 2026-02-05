#pragma once

#include <Standard.hpp>

#include <StepBasic_MeasureWithUnit.hpp>

class StepBasic_MassMeasureWithUnit : public StepBasic_MeasureWithUnit
{

public:
  //! Returns a MassMeasureWithUnit
  Standard_EXPORT StepBasic_MassMeasureWithUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_MassMeasureWithUnit, StepBasic_MeasureWithUnit)
};
