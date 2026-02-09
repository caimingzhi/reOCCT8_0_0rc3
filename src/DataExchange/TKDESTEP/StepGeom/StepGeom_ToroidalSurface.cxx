

#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_ToroidalSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_ToroidalSurface, StepGeom_ElementarySurface)

StepGeom_ToroidalSurface::StepGeom_ToroidalSurface() = default;

void StepGeom_ToroidalSurface::Init(const occ::handle<TCollection_HAsciiString>&  aName,
                                    const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                                    const double                                  aMajorRadius,
                                    const double                                  aMinorRadius)
{

  majorRadius = aMajorRadius;
  minorRadius = aMinorRadius;

  StepGeom_ElementarySurface::Init(aName, aPosition);
}

void StepGeom_ToroidalSurface::SetMajorRadius(const double aMajorRadius)
{
  majorRadius = aMajorRadius;
}

double StepGeom_ToroidalSurface::MajorRadius() const
{
  return majorRadius;
}

void StepGeom_ToroidalSurface::SetMinorRadius(const double aMinorRadius)
{
  minorRadius = aMinorRadius;
}

double StepGeom_ToroidalSurface::MinorRadius() const
{
  return minorRadius;
}
