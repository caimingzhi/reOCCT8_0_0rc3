#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_FacetedBrepShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  //! Returns a FacetedBrepShapeRepresentation
  Standard_EXPORT StepShape_FacetedBrepShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_FacetedBrepShapeRepresentation, StepShape_ShapeRepresentation)
};
