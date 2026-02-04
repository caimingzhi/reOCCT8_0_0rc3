#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedEdge.hpp>

//! Representation of STEP entity CubicBezierTessellatedEdge
class StepVisual_CubicBezierTessellatedEdge : public StepVisual_TessellatedEdge
{

public:
  //! default constructor
  Standard_EXPORT StepVisual_CubicBezierTessellatedEdge();

  DEFINE_STANDARD_RTTIEXT(StepVisual_CubicBezierTessellatedEdge, StepVisual_TessellatedEdge)
};

