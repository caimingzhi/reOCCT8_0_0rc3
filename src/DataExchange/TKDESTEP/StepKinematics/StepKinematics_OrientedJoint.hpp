#pragma once


#include <Standard.hpp>
#include <StepShape_OrientedEdge.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity OrientedJoint
class StepKinematics_OrientedJoint : public StepShape_OrientedEdge
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_OrientedJoint();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_OrientedJoint, StepShape_OrientedEdge)
};
