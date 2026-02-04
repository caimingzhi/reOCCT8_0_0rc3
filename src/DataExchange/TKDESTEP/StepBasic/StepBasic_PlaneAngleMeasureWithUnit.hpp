#pragma once


#include <Standard.hpp>

#include <StepBasic_MeasureWithUnit.hpp>

class StepBasic_PlaneAngleMeasureWithUnit : public StepBasic_MeasureWithUnit
{

public:
  //! Returns a PlaneAngleMeasureWithUnit
  Standard_EXPORT StepBasic_PlaneAngleMeasureWithUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_PlaneAngleMeasureWithUnit, StepBasic_MeasureWithUnit)
};

