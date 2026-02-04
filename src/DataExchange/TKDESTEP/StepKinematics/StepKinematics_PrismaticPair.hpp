#pragma once


#include <Standard.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity PrismaticPair
class StepKinematics_PrismaticPair : public StepKinematics_LowOrderKinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_PrismaticPair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PrismaticPair, StepKinematics_LowOrderKinematicPair)
};
