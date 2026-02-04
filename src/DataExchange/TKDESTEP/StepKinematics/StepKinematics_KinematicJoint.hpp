#pragma once


#include <Standard.hpp>
#include <StepShape_Edge.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity KinematicJoint
class StepKinematics_KinematicJoint : public StepShape_Edge
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_KinematicJoint();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicJoint, StepShape_Edge)
};
