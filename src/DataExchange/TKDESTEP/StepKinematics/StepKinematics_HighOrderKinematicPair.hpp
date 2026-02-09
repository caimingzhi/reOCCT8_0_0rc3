#pragma once

#include <Standard.hpp>
#include <StepKinematics_KinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_HighOrderKinematicPair : public StepKinematics_KinematicPair
{
public:
  Standard_EXPORT StepKinematics_HighOrderKinematicPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_HighOrderKinematicPair, StepKinematics_KinematicPair)
};
