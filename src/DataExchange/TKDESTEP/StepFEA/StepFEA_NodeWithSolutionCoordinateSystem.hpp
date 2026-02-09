#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_Node.hpp>

class StepFEA_NodeWithSolutionCoordinateSystem : public StepFEA_Node
{

public:
  Standard_EXPORT StepFEA_NodeWithSolutionCoordinateSystem();

  DEFINE_STANDARD_RTTIEXT(StepFEA_NodeWithSolutionCoordinateSystem, StepFEA_Node)
};
