#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_PreDefinedColour.hpp>

class StepVisual_DraughtingPreDefinedColour : public StepVisual_PreDefinedColour
{

public:
  //! Returns a DraughtingPreDefinedColour
  Standard_EXPORT StepVisual_DraughtingPreDefinedColour();

  DEFINE_STANDARD_RTTIEXT(StepVisual_DraughtingPreDefinedColour, StepVisual_PreDefinedColour)
};

