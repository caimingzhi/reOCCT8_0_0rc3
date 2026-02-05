#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_PreDefinedItem.hpp>

class StepVisual_PreDefinedTextFont : public StepVisual_PreDefinedItem
{

public:
  //! Returns a PreDefinedTextFont
  Standard_EXPORT StepVisual_PreDefinedTextFont();

  DEFINE_STANDARD_RTTIEXT(StepVisual_PreDefinedTextFont, StepVisual_PreDefinedItem)
};
