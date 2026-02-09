#pragma once

#include <Standard.hpp>
#include <StepKinematics_SurfacePair.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_RollingSurfacePair : public StepKinematics_SurfacePair
{
public:
  Standard_EXPORT StepKinematics_RollingSurfacePair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RollingSurfacePair, StepKinematics_SurfacePair)
};
