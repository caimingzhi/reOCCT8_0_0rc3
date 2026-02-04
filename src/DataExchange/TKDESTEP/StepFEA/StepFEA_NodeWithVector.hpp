#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_Node.hpp>

//! Representation of STEP entity NodeWithVector
class StepFEA_NodeWithVector : public StepFEA_Node
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_NodeWithVector();

  DEFINE_STANDARD_RTTIEXT(StepFEA_NodeWithVector, StepFEA_Node)
};

