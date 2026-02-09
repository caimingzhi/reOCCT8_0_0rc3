#include <StepGeom_OrientedSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_OrientedSurface, StepGeom_Surface)

StepGeom_OrientedSurface::StepGeom_OrientedSurface() = default;

void StepGeom_OrientedSurface::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const bool                                   aOrientation)
{
  StepGeom_Surface::Init(aRepresentationItem_Name);

  theOrientation = aOrientation;
}

bool StepGeom_OrientedSurface::Orientation() const
{
  return theOrientation;
}

void StepGeom_OrientedSurface::SetOrientation(const bool aOrientation)
{
  theOrientation = aOrientation;
}
