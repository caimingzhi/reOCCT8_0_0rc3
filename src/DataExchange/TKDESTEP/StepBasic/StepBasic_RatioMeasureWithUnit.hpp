#pragma once


#include <Standard.hpp>

#include <StepBasic_MeasureWithUnit.hpp>

class StepBasic_RatioMeasureWithUnit : public StepBasic_MeasureWithUnit
{

public:
  //! Returns a RatioMeasureWithUnit
  Standard_EXPORT StepBasic_RatioMeasureWithUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_RatioMeasureWithUnit, StepBasic_MeasureWithUnit)
};

