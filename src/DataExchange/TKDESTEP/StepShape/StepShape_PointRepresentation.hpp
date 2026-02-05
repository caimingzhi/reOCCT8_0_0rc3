#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

//! Representation of STEP entity PointRepresentation
class StepShape_PointRepresentation : public StepShape_ShapeRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_PointRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_PointRepresentation, StepShape_ShapeRepresentation)
};
