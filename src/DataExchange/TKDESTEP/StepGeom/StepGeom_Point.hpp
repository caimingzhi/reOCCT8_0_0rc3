#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>

class StepGeom_Point : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a Point
  Standard_EXPORT StepGeom_Point();

  DEFINE_STANDARD_RTTIEXT(StepGeom_Point, StepGeom_GeometricRepresentationItem)
};
