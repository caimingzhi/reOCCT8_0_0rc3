#pragma once


#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity RevolutePair
class StepKinematics_RevolutePair : public StepKinematics_LowOrderKinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_RevolutePair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RevolutePair, StepKinematics_LowOrderKinematicPair)
};
