

#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Placement.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Placement, StepGeom_GeometricRepresentationItem)

StepGeom_Placement::StepGeom_Placement() = default;

void StepGeom_Placement::Init(const occ::handle<TCollection_HAsciiString>& aName,
                              const occ::handle<StepGeom_CartesianPoint>&  aLocation)
{

  location = aLocation;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_Placement::SetLocation(const occ::handle<StepGeom_CartesianPoint>& aLocation)
{
  location = aLocation;
}

occ::handle<StepGeom_CartesianPoint> StepGeom_Placement::Location() const
{
  return location;
}
