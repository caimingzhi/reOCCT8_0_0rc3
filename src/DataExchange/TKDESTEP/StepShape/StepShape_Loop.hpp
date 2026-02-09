#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_TopologicalRepresentationItem.hpp>

class StepShape_Loop : public StepShape_TopologicalRepresentationItem
{

public:
  Standard_EXPORT StepShape_Loop();

  DEFINE_STANDARD_RTTIEXT(StepShape_Loop, StepShape_TopologicalRepresentationItem)
};
