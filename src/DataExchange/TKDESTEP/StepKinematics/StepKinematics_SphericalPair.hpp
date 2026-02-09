#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_SphericalPair : public StepKinematics_LowOrderKinematicPair
{
public:
  Standard_EXPORT StepKinematics_SphericalPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SphericalPair, StepKinematics_LowOrderKinematicPair)
};
