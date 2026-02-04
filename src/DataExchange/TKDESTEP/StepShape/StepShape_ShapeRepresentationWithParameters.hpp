#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

//! Representation of STEP entity ShapeRepresentationWithParameters
class StepShape_ShapeRepresentationWithParameters : public StepShape_ShapeRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_ShapeRepresentationWithParameters();

  DEFINE_STANDARD_RTTIEXT(StepShape_ShapeRepresentationWithParameters,
                          StepShape_ShapeRepresentation)
};

