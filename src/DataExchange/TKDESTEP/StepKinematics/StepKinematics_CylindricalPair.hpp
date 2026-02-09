#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_CylindricalPair : public StepKinematics_LowOrderKinematicPair
{
public:
  Standard_EXPORT StepKinematics_CylindricalPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_CylindricalPair, StepKinematics_LowOrderKinematicPair)
};
