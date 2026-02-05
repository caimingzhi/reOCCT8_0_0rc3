#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_NodeRepresentation.hpp>

//! Representation of STEP entity Node
class StepFEA_Node : public StepFEA_NodeRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_Node();

  DEFINE_STANDARD_RTTIEXT(StepFEA_Node, StepFEA_NodeRepresentation)
};
