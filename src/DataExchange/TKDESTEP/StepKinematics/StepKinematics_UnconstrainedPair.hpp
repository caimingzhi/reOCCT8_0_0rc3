#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_UnconstrainedPair : public StepKinematics_LowOrderKinematicPair
{
public:
  Standard_EXPORT StepKinematics_UnconstrainedPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_UnconstrainedPair, StepKinematics_LowOrderKinematicPair)
};
