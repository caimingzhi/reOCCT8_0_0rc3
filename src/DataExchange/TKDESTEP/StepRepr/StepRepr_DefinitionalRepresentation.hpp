#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>

class StepRepr_DefinitionalRepresentation : public StepRepr_Representation
{

public:
  Standard_EXPORT StepRepr_DefinitionalRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepRepr_DefinitionalRepresentation, StepRepr_Representation)
};
