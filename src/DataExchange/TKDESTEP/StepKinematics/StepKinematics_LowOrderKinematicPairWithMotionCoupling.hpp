#pragma once

#include <Standard.hpp>
#include <StepKinematics_KinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity LowOrderKinematicPairWithMotionCoupling
class StepKinematics_LowOrderKinematicPairWithMotionCoupling : public StepKinematics_KinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_LowOrderKinematicPairWithMotionCoupling();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_LowOrderKinematicPairWithMotionCoupling,
                          StepKinematics_KinematicPair)
};
