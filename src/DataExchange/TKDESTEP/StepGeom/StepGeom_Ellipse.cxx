

#include <StepGeom_Ellipse.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Ellipse, StepGeom_Conic)

StepGeom_Ellipse::StepGeom_Ellipse() = default;

void StepGeom_Ellipse::Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepGeom_Axis2Placement&               aPosition,
                            const double                                 aSemiAxis1,
                            const double                                 aSemiAxis2)
{

  semiAxis1 = aSemiAxis1;
  semiAxis2 = aSemiAxis2;

  StepGeom_Conic::Init(aName, aPosition);
}

void StepGeom_Ellipse::SetSemiAxis1(const double aSemiAxis1)
{
  semiAxis1 = aSemiAxis1;
}

double StepGeom_Ellipse::SemiAxis1() const
{
  return semiAxis1;
}

void StepGeom_Ellipse::SetSemiAxis2(const double aSemiAxis2)
{
  semiAxis2 = aSemiAxis2;
}

double StepGeom_Ellipse::SemiAxis2() const
{
  return semiAxis2;
}
