#pragma once


#include <Standard.hpp>

#include <StepGeom_SurfaceCurve.hpp>

class StepGeom_IntersectionCurve : public StepGeom_SurfaceCurve
{

public:
  //! Returns a IntersectionCurve
  Standard_EXPORT StepGeom_IntersectionCurve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_IntersectionCurve, StepGeom_SurfaceCurve)
};

