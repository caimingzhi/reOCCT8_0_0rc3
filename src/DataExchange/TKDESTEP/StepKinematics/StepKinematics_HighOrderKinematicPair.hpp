#pragma once

#include <Standard.hpp>
#include <StepKinematics_KinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity HighOrderKinematicPair
class StepKinematics_HighOrderKinematicPair : public StepKinematics_KinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_HighOrderKinematicPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_HighOrderKinematicPair, StepKinematics_KinematicPair)
};
