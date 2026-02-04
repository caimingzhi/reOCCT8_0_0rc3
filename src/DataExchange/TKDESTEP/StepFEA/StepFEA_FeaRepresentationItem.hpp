#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>

//! Representation of STEP entity FeaRepresentationItem
class StepFEA_FeaRepresentationItem : public StepRepr_RepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaRepresentationItem();

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaRepresentationItem, StepRepr_RepresentationItem)
};

