#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity SphericalPair
class StepKinematics_SphericalPair : public StepKinematics_LowOrderKinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_SphericalPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SphericalPair, StepKinematics_LowOrderKinematicPair)
};
