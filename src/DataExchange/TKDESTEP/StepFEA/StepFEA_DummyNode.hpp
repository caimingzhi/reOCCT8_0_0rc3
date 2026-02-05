#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_NodeRepresentation.hpp>

//! Representation of STEP entity DummyNode
class StepFEA_DummyNode : public StepFEA_NodeRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_DummyNode();

  DEFINE_STANDARD_RTTIEXT(StepFEA_DummyNode, StepFEA_NodeRepresentation)
};
