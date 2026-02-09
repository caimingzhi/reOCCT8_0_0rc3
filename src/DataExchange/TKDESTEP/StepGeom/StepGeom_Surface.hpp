#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>

class StepGeom_Surface : public StepGeom_GeometricRepresentationItem
{

public:
  Standard_EXPORT StepGeom_Surface();

  DEFINE_STANDARD_RTTIEXT(StepGeom_Surface, StepGeom_GeometricRepresentationItem)
};
