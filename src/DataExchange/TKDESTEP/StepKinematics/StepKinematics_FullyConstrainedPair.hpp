#pragma once


#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity FullyConstrainedPair
class StepKinematics_FullyConstrainedPair : public StepKinematics_LowOrderKinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_FullyConstrainedPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_FullyConstrainedPair, StepKinematics_LowOrderKinematicPair)
};
