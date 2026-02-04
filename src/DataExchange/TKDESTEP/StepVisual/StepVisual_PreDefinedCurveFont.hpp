#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_PreDefinedItem.hpp>

class StepVisual_PreDefinedCurveFont : public StepVisual_PreDefinedItem
{

public:
  //! Returns a PreDefinedCurveFont
  Standard_EXPORT StepVisual_PreDefinedCurveFont();

  DEFINE_STANDARD_RTTIEXT(StepVisual_PreDefinedCurveFont, StepVisual_PreDefinedItem)
};

