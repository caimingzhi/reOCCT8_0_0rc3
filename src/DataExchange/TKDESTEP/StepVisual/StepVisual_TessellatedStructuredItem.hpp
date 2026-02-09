#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedItem.hpp>

class StepVisual_TessellatedStructuredItem : public StepVisual_TessellatedItem
{

public:
  Standard_EXPORT StepVisual_TessellatedStructuredItem();

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedStructuredItem, StepVisual_TessellatedItem)
};
