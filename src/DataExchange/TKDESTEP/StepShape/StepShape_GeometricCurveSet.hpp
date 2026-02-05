#pragma once

#include <Standard.hpp>

#include <StepShape_GeometricSet.hpp>

class StepShape_GeometricCurveSet : public StepShape_GeometricSet
{

public:
  //! Returns a GeometricCurveSet
  Standard_EXPORT StepShape_GeometricCurveSet();

  DEFINE_STANDARD_RTTIEXT(StepShape_GeometricCurveSet, StepShape_GeometricSet)
};
