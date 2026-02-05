#pragma once

#include <Standard.hpp>

#include <StepBasic_ExternallyDefinedItem.hpp>

//! Representation of STEP entity ExternallyDefinedTextFont
class StepVisual_ExternallyDefinedTextFont : public StepBasic_ExternallyDefinedItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepVisual_ExternallyDefinedTextFont();

  DEFINE_STANDARD_RTTIEXT(StepVisual_ExternallyDefinedTextFont, StepBasic_ExternallyDefinedItem)
};
