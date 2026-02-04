#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>

class StepVisual_PresentationRepresentation : public StepRepr_Representation
{

public:
  //! Returns a PresentationRepresentation
  Standard_EXPORT StepVisual_PresentationRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepVisual_PresentationRepresentation, StepRepr_Representation)
};

