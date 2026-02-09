#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>

class StepRepr_ConstructiveGeometryRepresentation : public StepRepr_Representation
{
public:
  Standard_EXPORT StepRepr_ConstructiveGeometryRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ConstructiveGeometryRepresentation, StepRepr_Representation)
};
