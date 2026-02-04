#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_Node.hpp>

//! Representation of STEP entity NodeWithSolutionCoordinateSystem
class StepFEA_NodeWithSolutionCoordinateSystem : public StepFEA_Node
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_NodeWithSolutionCoordinateSystem();

  DEFINE_STANDARD_RTTIEXT(StepFEA_NodeWithSolutionCoordinateSystem, StepFEA_Node)
};

