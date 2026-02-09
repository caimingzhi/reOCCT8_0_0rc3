#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_SphericalPairWithPin : public StepKinematics_LowOrderKinematicPair
{
public:
  Standard_EXPORT StepKinematics_SphericalPairWithPin();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SphericalPairWithPin, StepKinematics_LowOrderKinematicPair)
};
