#pragma once


#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity PlanarPair
class StepKinematics_PlanarPair : public StepKinematics_LowOrderKinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_PlanarPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PlanarPair, StepKinematics_LowOrderKinematicPair)
};
