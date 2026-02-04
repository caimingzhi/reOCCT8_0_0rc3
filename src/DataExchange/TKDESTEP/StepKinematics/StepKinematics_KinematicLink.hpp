#pragma once


#include <Standard.hpp>
#include <StepShape_Vertex.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity KinematicLink
class StepKinematics_KinematicLink : public StepShape_Vertex
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_KinematicLink();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicLink, StepShape_Vertex)
};
