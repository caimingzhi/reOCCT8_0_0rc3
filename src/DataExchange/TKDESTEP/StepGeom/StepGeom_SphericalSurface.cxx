

#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_SphericalSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_SphericalSurface, StepGeom_ElementarySurface)

StepGeom_SphericalSurface::StepGeom_SphericalSurface() = default;

void StepGeom_SphericalSurface::Init(const occ::handle<TCollection_HAsciiString>&  aName,
                                     const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                                     const double                                  aRadius)
{

  radius = aRadius;

  StepGeom_ElementarySurface::Init(aName, aPosition);
}

void StepGeom_SphericalSurface::SetRadius(const double aRadius)
{
  radius = aRadius;
}

double StepGeom_SphericalSurface::Radius() const
{
  return radius;
}
