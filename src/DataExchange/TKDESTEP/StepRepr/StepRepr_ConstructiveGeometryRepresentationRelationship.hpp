#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationRelationship.hpp>

class StepRepr_ConstructiveGeometryRepresentationRelationship
    : public StepRepr_RepresentationRelationship
{
public:
  Standard_EXPORT StepRepr_ConstructiveGeometryRepresentationRelationship();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ConstructiveGeometryRepresentationRelationship,
                          StepRepr_RepresentationRelationship)
};
