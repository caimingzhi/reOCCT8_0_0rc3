#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_BSplineCurve.hpp>

class StepGeom_QuasiUniformCurve : public StepGeom_BSplineCurve
{

public:
  //! Returns a QuasiUniformCurve
  Standard_EXPORT StepGeom_QuasiUniformCurve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_QuasiUniformCurve, StepGeom_BSplineCurve)
};
