#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_MappedItem.hpp>

class StepVisual_AnnotationText : public StepRepr_MappedItem
{

public:
  //! Returns a AnnotationText
  Standard_EXPORT StepVisual_AnnotationText();

  DEFINE_STANDARD_RTTIEXT(StepVisual_AnnotationText, StepRepr_MappedItem)
};
