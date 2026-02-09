#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>

class StepGeom_Curve : public StepGeom_GeometricRepresentationItem
{

public:
  Standard_EXPORT StepGeom_Curve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_Curve, StepGeom_GeometricRepresentationItem)
};
