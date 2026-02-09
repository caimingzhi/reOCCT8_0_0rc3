

#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_CylindricalSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_CylindricalSurface, StepGeom_ElementarySurface)

StepGeom_CylindricalSurface::StepGeom_CylindricalSurface() = default;

void StepGeom_CylindricalSurface::Init(const occ::handle<TCollection_HAsciiString>&  aName,
                                       const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                                       const double                                  aRadius)
{

  radius = aRadius;

  StepGeom_ElementarySurface::Init(aName, aPosition);
}

void StepGeom_CylindricalSurface::SetRadius(const double aRadius)
{
  radius = aRadius;
}

double StepGeom_CylindricalSurface::Radius() const
{
  return radius;
}
