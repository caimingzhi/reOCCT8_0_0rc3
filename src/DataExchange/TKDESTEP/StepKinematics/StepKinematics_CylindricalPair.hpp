#pragma once

#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity CylindricalPair
class StepKinematics_CylindricalPair : public StepKinematics_LowOrderKinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_CylindricalPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_CylindricalPair, StepKinematics_LowOrderKinematicPair)
};
