#pragma once

#include <Standard.hpp>
#include <StepKinematics_UniversalPair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity HomokineticPair
class StepKinematics_HomokineticPair : public StepKinematics_UniversalPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_HomokineticPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_HomokineticPair, StepKinematics_UniversalPair)
};
