#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_NodeRepresentation.hpp>

class StepFEA_Node : public StepFEA_NodeRepresentation
{

public:
  Standard_EXPORT StepFEA_Node();

  DEFINE_STANDARD_RTTIEXT(StepFEA_Node, StepFEA_NodeRepresentation)
};
