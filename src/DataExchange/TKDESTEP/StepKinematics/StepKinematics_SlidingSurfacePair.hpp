#pragma once

#include <Standard.hpp>
#include <StepKinematics_SurfacePair.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_SlidingSurfacePair : public StepKinematics_SurfacePair
{
public:
  Standard_EXPORT StepKinematics_SlidingSurfacePair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SlidingSurfacePair, StepKinematics_SurfacePair)
};
