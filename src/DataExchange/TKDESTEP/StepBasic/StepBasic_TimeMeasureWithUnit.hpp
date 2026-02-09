#pragma once

#include <Standard.hpp>

#include <StepBasic_MeasureWithUnit.hpp>

class StepBasic_TimeMeasureWithUnit : public StepBasic_MeasureWithUnit
{

public:
  Standard_EXPORT StepBasic_TimeMeasureWithUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_TimeMeasureWithUnit, StepBasic_MeasureWithUnit)
};
