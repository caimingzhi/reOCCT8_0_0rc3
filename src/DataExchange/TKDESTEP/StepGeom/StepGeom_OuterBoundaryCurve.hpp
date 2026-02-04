#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_BoundaryCurve.hpp>

class StepGeom_OuterBoundaryCurve : public StepGeom_BoundaryCurve
{

public:
  //! Returns a OuterBoundaryCurve
  Standard_EXPORT StepGeom_OuterBoundaryCurve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_OuterBoundaryCurve, StepGeom_BoundaryCurve)
};

