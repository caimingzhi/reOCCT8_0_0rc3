#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_RevolutePair : public StepKinematics_LowOrderKinematicPair
{
public:
  Standard_EXPORT StepKinematics_RevolutePair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RevolutePair, StepKinematics_LowOrderKinematicPair)
};
