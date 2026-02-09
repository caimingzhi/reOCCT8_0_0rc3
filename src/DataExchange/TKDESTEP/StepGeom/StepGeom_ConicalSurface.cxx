

#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_ConicalSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_ConicalSurface, StepGeom_ElementarySurface)

StepGeom_ConicalSurface::StepGeom_ConicalSurface() = default;

void StepGeom_ConicalSurface::Init(const occ::handle<TCollection_HAsciiString>&  aName,
                                   const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                                   const double                                  aRadius,
                                   const double                                  aSemiAngle)
{

  radius    = aRadius;
  semiAngle = aSemiAngle;

  StepGeom_ElementarySurface::Init(aName, aPosition);
}

void StepGeom_ConicalSurface::SetRadius(const double aRadius)
{
  radius = aRadius;
}

double StepGeom_ConicalSurface::Radius() const
{
  return radius;
}

void StepGeom_ConicalSurface::SetSemiAngle(const double aSemiAngle)
{
  semiAngle = aSemiAngle;
}

double StepGeom_ConicalSurface::SemiAngle() const
{
  return semiAngle;
}
