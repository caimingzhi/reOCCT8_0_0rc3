#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>

class StepShape_SolidModel : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a SolidModel
  Standard_EXPORT StepShape_SolidModel();

  DEFINE_STANDARD_RTTIEXT(StepShape_SolidModel, StepGeom_GeometricRepresentationItem)
};

