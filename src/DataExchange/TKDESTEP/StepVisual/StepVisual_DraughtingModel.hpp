#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>

//! Representation of STEP entity DraughtingModel
class StepVisual_DraughtingModel : public StepRepr_Representation
{

public:
  //! Empty constructor
  Standard_EXPORT StepVisual_DraughtingModel();

  DEFINE_STANDARD_RTTIEXT(StepVisual_DraughtingModel, StepRepr_Representation)
};

