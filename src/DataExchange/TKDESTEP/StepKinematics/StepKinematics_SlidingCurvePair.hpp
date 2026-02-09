#pragma once

#include <Standard.hpp>
#include <StepKinematics_PlanarCurvePair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepGeom_Curve.hpp>

class StepKinematics_SlidingCurvePair : public StepKinematics_PlanarCurvePair
{
public:
  Standard_EXPORT StepKinematics_SlidingCurvePair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SlidingCurvePair, StepKinematics_PlanarCurvePair)
};
