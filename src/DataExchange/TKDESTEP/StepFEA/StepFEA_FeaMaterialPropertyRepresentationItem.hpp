#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>

//! Representation of STEP entity FeaMaterialPropertyRepresentationItem
class StepFEA_FeaMaterialPropertyRepresentationItem : public StepRepr_RepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaMaterialPropertyRepresentationItem();

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaMaterialPropertyRepresentationItem,
                          StepRepr_RepresentationItem)
};
