#pragma once

#include <Standard.hpp>
#include <StepKinematics_UniversalPair.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_HomokineticPair : public StepKinematics_UniversalPair
{
public:
  Standard_EXPORT StepKinematics_HomokineticPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_HomokineticPair, StepKinematics_UniversalPair)
};
