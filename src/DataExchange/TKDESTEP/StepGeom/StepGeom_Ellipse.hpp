#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <StepGeom_Conic.hpp>
class TCollection_HAsciiString;
class StepGeom_Axis2Placement;

class StepGeom_Ellipse : public StepGeom_Conic
{

public:
  //! Returns a Ellipse
  Standard_EXPORT StepGeom_Ellipse();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepGeom_Axis2Placement&               aPosition,
                            const double                                 aSemiAxis1,
                            const double                                 aSemiAxis2);

  Standard_EXPORT void SetSemiAxis1(const double aSemiAxis1);

  Standard_EXPORT double SemiAxis1() const;

  Standard_EXPORT void SetSemiAxis2(const double aSemiAxis2);

  Standard_EXPORT double SemiAxis2() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Ellipse, StepGeom_Conic)

private:
  double semiAxis1;
  double semiAxis2;
};
