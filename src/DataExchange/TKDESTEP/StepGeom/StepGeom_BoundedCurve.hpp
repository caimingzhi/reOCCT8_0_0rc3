#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_Curve.hpp>

class StepGeom_BoundedCurve : public StepGeom_Curve
{

public:
  //! Returns a BoundedCurve
  Standard_EXPORT StepGeom_BoundedCurve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_BoundedCurve, StepGeom_Curve)
};

