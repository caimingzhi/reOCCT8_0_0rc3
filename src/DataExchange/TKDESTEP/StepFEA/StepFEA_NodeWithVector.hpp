#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_Node.hpp>

class StepFEA_NodeWithVector : public StepFEA_Node
{

public:
  Standard_EXPORT StepFEA_NodeWithVector();

  DEFINE_STANDARD_RTTIEXT(StepFEA_NodeWithVector, StepFEA_Node)
};
