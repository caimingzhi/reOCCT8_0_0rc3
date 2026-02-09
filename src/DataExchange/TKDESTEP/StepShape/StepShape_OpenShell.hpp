#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ConnectedFaceSet.hpp>

class StepShape_OpenShell : public StepShape_ConnectedFaceSet
{

public:
  Standard_EXPORT StepShape_OpenShell();

  DEFINE_STANDARD_RTTIEXT(StepShape_OpenShell, StepShape_ConnectedFaceSet)
};
