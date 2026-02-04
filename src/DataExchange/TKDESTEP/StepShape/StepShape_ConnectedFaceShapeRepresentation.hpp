#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>

//! Representation of STEP entity ConnectedFaceShapeRepresentation
class StepShape_ConnectedFaceShapeRepresentation : public StepRepr_Representation
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_ConnectedFaceShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_ConnectedFaceShapeRepresentation, StepRepr_Representation)
};

