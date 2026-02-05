#pragma once

#include <Standard.hpp>

#include <StepBasic_ExternallyDefinedItem.hpp>

//! Representation of STEP entity ExternallyDefinedCurveFont
class StepVisual_ExternallyDefinedCurveFont : public StepBasic_ExternallyDefinedItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepVisual_ExternallyDefinedCurveFont();

  DEFINE_STANDARD_RTTIEXT(StepVisual_ExternallyDefinedCurveFont, StepBasic_ExternallyDefinedItem)
};
