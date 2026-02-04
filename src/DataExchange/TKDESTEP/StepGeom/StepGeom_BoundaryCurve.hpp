#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_CompositeCurveOnSurface.hpp>

class StepGeom_BoundaryCurve : public StepGeom_CompositeCurveOnSurface
{

public:
  //! Returns a BoundaryCurve
  Standard_EXPORT StepGeom_BoundaryCurve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_BoundaryCurve, StepGeom_CompositeCurveOnSurface)
};

