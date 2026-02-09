#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspectRelationship.hpp>

class StepRepr_FeatureForDatumTargetRelationship : public StepRepr_ShapeAspectRelationship
{

public:
  Standard_EXPORT StepRepr_FeatureForDatumTargetRelationship();

  DEFINE_STANDARD_RTTIEXT(StepRepr_FeatureForDatumTargetRelationship,
                          StepRepr_ShapeAspectRelationship)
};
