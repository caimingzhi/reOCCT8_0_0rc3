#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <StepGeom_Conic.hpp>
class TCollection_HAsciiString;
class StepGeom_Axis2Placement;

class StepGeom_Hyperbola : public StepGeom_Conic
{

public:
  Standard_EXPORT StepGeom_Hyperbola();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepGeom_Axis2Placement&               aPosition,
                            const double                                 aSemiAxis,
                            const double                                 aSemiImagAxis);

  Standard_EXPORT void SetSemiAxis(const double aSemiAxis);

  Standard_EXPORT double SemiAxis() const;

  Standard_EXPORT void SetSemiImagAxis(const double aSemiImagAxis);

  Standard_EXPORT double SemiImagAxis() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Hyperbola, StepGeom_Conic)

private:
  double semiAxis;
  double semiImagAxis;
};
