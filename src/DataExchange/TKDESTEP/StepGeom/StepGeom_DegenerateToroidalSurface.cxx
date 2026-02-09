

#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_DegenerateToroidalSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_DegenerateToroidalSurface, StepGeom_ToroidalSurface)

StepGeom_DegenerateToroidalSurface::StepGeom_DegenerateToroidalSurface() = default;

void StepGeom_DegenerateToroidalSurface::Init(
  const occ::handle<TCollection_HAsciiString>&  aName,
  const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
  const double                                  aMajorRadius,
  const double                                  aMinorRadius,
  const bool                                    aSelectOuter)
{

  selectOuter = aSelectOuter;

  StepGeom_ToroidalSurface::Init(aName, aPosition, aMajorRadius, aMinorRadius);
}

void StepGeom_DegenerateToroidalSurface::SetSelectOuter(const bool aSelectOuter)
{
  selectOuter = aSelectOuter;
}

bool StepGeom_DegenerateToroidalSurface::SelectOuter() const
{
  return selectOuter;
}
