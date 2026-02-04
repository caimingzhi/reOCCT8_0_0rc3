#pragma once


#include <Standard.hpp>

#include <StepGeom_SurfaceCurve.hpp>

class StepGeom_SeamCurve : public StepGeom_SurfaceCurve
{

public:
  //! Returns a SeamCurve
  Standard_EXPORT StepGeom_SeamCurve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_SeamCurve, StepGeom_SurfaceCurve)
};

