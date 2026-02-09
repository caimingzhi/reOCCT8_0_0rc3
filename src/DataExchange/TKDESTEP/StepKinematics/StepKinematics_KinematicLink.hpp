#pragma once

#include <Standard.hpp>
#include <StepShape_Vertex.hpp>

#include <TCollection_HAsciiString.hpp>

class StepKinematics_KinematicLink : public StepShape_Vertex
{
public:
  Standard_EXPORT StepKinematics_KinematicLink();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicLink, StepShape_Vertex)
};
