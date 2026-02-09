#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_NodeRepresentation.hpp>

class StepFEA_DummyNode : public StepFEA_NodeRepresentation
{

public:
  Standard_EXPORT StepFEA_DummyNode();

  DEFINE_STANDARD_RTTIEXT(StepFEA_DummyNode, StepFEA_NodeRepresentation)
};
