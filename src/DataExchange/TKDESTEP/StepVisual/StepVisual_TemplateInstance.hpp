#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_MappedItem.hpp>

class StepVisual_TemplateInstance : public StepRepr_MappedItem
{

public:
  //! Returns a TemplateInstance
  Standard_EXPORT StepVisual_TemplateInstance();

  DEFINE_STANDARD_RTTIEXT(StepVisual_TemplateInstance, StepRepr_MappedItem)
};

