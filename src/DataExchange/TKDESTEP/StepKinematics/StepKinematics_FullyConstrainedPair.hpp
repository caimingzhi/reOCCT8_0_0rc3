#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_FullyConstrainedPair : public StepKinematics_LowOrderKinematicPair
{
public:
  Standard_EXPORT StepKinematics_FullyConstrainedPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_FullyConstrainedPair, StepKinematics_LowOrderKinematicPair)
};
