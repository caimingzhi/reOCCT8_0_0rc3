#pragma once


#include <Standard.hpp>

#include <StepBasic_MeasureWithUnit.hpp>

class StepBasic_LengthMeasureWithUnit : public StepBasic_MeasureWithUnit
{

public:
  //! Returns a LengthMeasureWithUnit
  Standard_EXPORT StepBasic_LengthMeasureWithUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_LengthMeasureWithUnit, StepBasic_MeasureWithUnit)
};

