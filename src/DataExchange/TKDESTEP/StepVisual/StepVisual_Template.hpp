#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>

class StepVisual_Template : public StepRepr_Representation
{

public:
  //! Returns a Template
  Standard_EXPORT StepVisual_Template();

  DEFINE_STANDARD_RTTIEXT(StepVisual_Template, StepRepr_Representation)
};

