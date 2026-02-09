#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_TopologicalRepresentationItem.hpp>

class StepShape_Vertex : public StepShape_TopologicalRepresentationItem
{

public:
  Standard_EXPORT StepShape_Vertex();

  DEFINE_STANDARD_RTTIEXT(StepShape_Vertex, StepShape_TopologicalRepresentationItem)
};
