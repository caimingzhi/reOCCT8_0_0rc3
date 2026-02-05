#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_ManifoldSurfaceShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  //! Returns a ManifoldSurfaceShapeRepresentation
  Standard_EXPORT StepShape_ManifoldSurfaceShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_ManifoldSurfaceShapeRepresentation,
                          StepShape_ShapeRepresentation)
};
