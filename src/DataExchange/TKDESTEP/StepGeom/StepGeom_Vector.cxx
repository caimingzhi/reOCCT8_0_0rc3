

#include <StepGeom_Direction.hpp>
#include <StepGeom_Vector.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Vector, StepGeom_GeometricRepresentationItem)

StepGeom_Vector::StepGeom_Vector() = default;

void StepGeom_Vector::Init(const occ::handle<TCollection_HAsciiString>& aName,
                           const occ::handle<StepGeom_Direction>&       aOrientation,
                           const double                                 aMagnitude)
{

  orientation = aOrientation;
  magnitude   = aMagnitude;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_Vector::SetOrientation(const occ::handle<StepGeom_Direction>& aOrientation)
{
  orientation = aOrientation;
}

occ::handle<StepGeom_Direction> StepGeom_Vector::Orientation() const
{
  return orientation;
}

void StepGeom_Vector::SetMagnitude(const double aMagnitude)
{
  magnitude = aMagnitude;
}

double StepGeom_Vector::Magnitude() const
{
  return magnitude;
}
