#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspectRelationship.hpp>

//! Representation of STEP entity DimensionalLocation
class StepRepr_FeatureForDatumTargetRelationship : public StepRepr_ShapeAspectRelationship
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_FeatureForDatumTargetRelationship();

  DEFINE_STANDARD_RTTIEXT(StepRepr_FeatureForDatumTargetRelationship,
                          StepRepr_ShapeAspectRelationship)
};

