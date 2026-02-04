#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_BSplineCurve.hpp>

class StepGeom_BezierCurve : public StepGeom_BSplineCurve
{

public:
  //! Returns a BezierCurve
  Standard_EXPORT StepGeom_BezierCurve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_BezierCurve, StepGeom_BSplineCurve)
};

