#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>

class StepShape_TopologicalRepresentationItem : public StepRepr_RepresentationItem
{

public:
  //! Returns a TopologicalRepresentationItem
  Standard_EXPORT StepShape_TopologicalRepresentationItem();

  DEFINE_STANDARD_RTTIEXT(StepShape_TopologicalRepresentationItem, StepRepr_RepresentationItem)
};
