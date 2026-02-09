

#include <StepGeom_Circle.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Circle, StepGeom_Conic)

StepGeom_Circle::StepGeom_Circle() = default;

void StepGeom_Circle::Init(const occ::handle<TCollection_HAsciiString>& aName,
                           const StepGeom_Axis2Placement&               aPosition,
                           const double                                 aRadius)
{

  radius = aRadius;

  StepGeom_Conic::Init(aName, aPosition);
}

void StepGeom_Circle::SetRadius(const double aRadius)
{
  radius = aRadius;
}

double StepGeom_Circle::Radius() const
{
  return radius;
}
