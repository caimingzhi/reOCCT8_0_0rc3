#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

//! Representation of STEP entity NonManifoldSurfaceShapeRepresentation
class StepShape_NonManifoldSurfaceShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_NonManifoldSurfaceShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_NonManifoldSurfaceShapeRepresentation,
                          StepShape_ShapeRepresentation)
};

