#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepShape_ShapeRepresentation.hpp>

//! Representation of STEP entity TessellatedShapeRepresentation
class StepVisual_TessellatedShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  //! default constructor
  Standard_EXPORT StepVisual_TessellatedShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedShapeRepresentation, StepShape_ShapeRepresentation)
};

