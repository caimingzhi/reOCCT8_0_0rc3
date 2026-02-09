#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_NodeRepresentation.hpp>

class StepFEA_GeometricNode : public StepFEA_NodeRepresentation
{

public:
  Standard_EXPORT StepFEA_GeometricNode();

  DEFINE_STANDARD_RTTIEXT(StepFEA_GeometricNode, StepFEA_NodeRepresentation)
};
