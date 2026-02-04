#pragma once


#include <Standard.hpp>
#include <StepKinematics_SurfacePair.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity SlidingSurfacePair
class StepKinematics_SlidingSurfacePair : public StepKinematics_SurfacePair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_SlidingSurfacePair();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SlidingSurfacePair, StepKinematics_SurfacePair)
};
