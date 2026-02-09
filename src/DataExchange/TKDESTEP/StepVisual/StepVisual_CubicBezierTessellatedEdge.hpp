#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedEdge.hpp>

class StepVisual_CubicBezierTessellatedEdge : public StepVisual_TessellatedEdge
{

public:
  Standard_EXPORT StepVisual_CubicBezierTessellatedEdge();

  DEFINE_STANDARD_RTTIEXT(StepVisual_CubicBezierTessellatedEdge, StepVisual_TessellatedEdge)
};
