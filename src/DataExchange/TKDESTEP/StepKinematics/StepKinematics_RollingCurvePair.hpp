#pragma once

#include <Standard.hpp>
#include <StepKinematics_PlanarCurvePair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepGeom_Curve.hpp>

//! Representation of STEP entity RollingCurvePair
class StepKinematics_RollingCurvePair : public StepKinematics_PlanarCurvePair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_RollingCurvePair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RollingCurvePair, StepKinematics_PlanarCurvePair)
};
