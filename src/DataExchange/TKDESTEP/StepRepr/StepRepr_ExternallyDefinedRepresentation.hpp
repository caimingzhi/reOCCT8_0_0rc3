#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>

class StepRepr_ExternallyDefinedRepresentation : public StepRepr_Representation
{

public:
  Standard_EXPORT StepRepr_ExternallyDefinedRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ExternallyDefinedRepresentation, StepRepr_Representation)
};

