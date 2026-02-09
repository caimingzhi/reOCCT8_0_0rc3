#pragma once

#include <Standard.hpp>

#include <StepBasic_MeasureWithUnit.hpp>

class StepBasic_SolidAngleMeasureWithUnit : public StepBasic_MeasureWithUnit
{

public:
  Standard_EXPORT StepBasic_SolidAngleMeasureWithUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_SolidAngleMeasureWithUnit, StepBasic_MeasureWithUnit)
};
