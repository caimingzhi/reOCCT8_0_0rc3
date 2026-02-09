#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_DraughtingModel.hpp>

class StepVisual_CharacterizedObjAndRepresentationAndDraughtingModel
    : public StepVisual_DraughtingModel
{

public:
  Standard_EXPORT StepVisual_CharacterizedObjAndRepresentationAndDraughtingModel();

  DEFINE_STANDARD_RTTIEXT(StepVisual_CharacterizedObjAndRepresentationAndDraughtingModel,
                          StepVisual_DraughtingModel)
};
