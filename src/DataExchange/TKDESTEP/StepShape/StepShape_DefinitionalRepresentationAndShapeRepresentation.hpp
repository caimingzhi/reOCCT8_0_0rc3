#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_DefinitionalRepresentation.hpp>

//! Implements complex type
//! (DEFINITIONAL_REPRESENTATION,REPRESENTATION,SHAPE_REPRESENTATION)
class StepShape_DefinitionalRepresentationAndShapeRepresentation
    : public StepRepr_DefinitionalRepresentation
{

public:
  Standard_EXPORT StepShape_DefinitionalRepresentationAndShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_DefinitionalRepresentationAndShapeRepresentation,
                          StepRepr_DefinitionalRepresentation)
};

