#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_PreDefinedCurveFont.hpp>

class StepVisual_DraughtingPreDefinedCurveFont : public StepVisual_PreDefinedCurveFont
{

public:
  //! Returns a DraughtingPreDefinedCurveFont
  Standard_EXPORT StepVisual_DraughtingPreDefinedCurveFont();

  DEFINE_STANDARD_RTTIEXT(StepVisual_DraughtingPreDefinedCurveFont, StepVisual_PreDefinedCurveFont)
};
