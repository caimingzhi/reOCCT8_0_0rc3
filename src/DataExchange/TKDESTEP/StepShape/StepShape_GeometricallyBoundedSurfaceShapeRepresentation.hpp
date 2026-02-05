#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_GeometricallyBoundedSurfaceShapeRepresentation
    : public StepShape_ShapeRepresentation
{

public:
  //! Returns a GeometricallyBoundedSurfaceShapeRepresentation
  Standard_EXPORT StepShape_GeometricallyBoundedSurfaceShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_GeometricallyBoundedSurfaceShapeRepresentation,
                          StepShape_ShapeRepresentation)
};
