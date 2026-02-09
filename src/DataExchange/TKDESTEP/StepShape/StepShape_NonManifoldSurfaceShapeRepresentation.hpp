#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_NonManifoldSurfaceShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  Standard_EXPORT StepShape_NonManifoldSurfaceShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_NonManifoldSurfaceShapeRepresentation,
                          StepShape_ShapeRepresentation)
};
