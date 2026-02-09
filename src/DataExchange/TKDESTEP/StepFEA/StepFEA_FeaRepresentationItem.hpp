#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>

class StepFEA_FeaRepresentationItem : public StepRepr_RepresentationItem
{

public:
  Standard_EXPORT StepFEA_FeaRepresentationItem();

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaRepresentationItem, StepRepr_RepresentationItem)
};
