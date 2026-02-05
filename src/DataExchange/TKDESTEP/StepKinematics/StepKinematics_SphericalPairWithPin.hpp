#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity SphericalPairWithPin
class StepKinematics_SphericalPairWithPin : public StepKinematics_LowOrderKinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_SphericalPairWithPin();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SphericalPairWithPin, StepKinematics_LowOrderKinematicPair)
};
