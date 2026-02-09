

#include <StepGeom_GeometricRepresentationContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_GeometricRepresentationContext, StepRepr_RepresentationContext)

StepGeom_GeometricRepresentationContext::StepGeom_GeometricRepresentationContext() = default;

void StepGeom_GeometricRepresentationContext::Init(
  const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
  const occ::handle<TCollection_HAsciiString>& aContextType,
  const int                                    aCoordinateSpaceDimension)
{

  coordinateSpaceDimension = aCoordinateSpaceDimension;

  StepRepr_RepresentationContext::Init(aContextIdentifier, aContextType);
}

void StepGeom_GeometricRepresentationContext::SetCoordinateSpaceDimension(
  const int aCoordinateSpaceDimension)
{
  coordinateSpaceDimension = aCoordinateSpaceDimension;
}

int StepGeom_GeometricRepresentationContext::CoordinateSpaceDimension() const
{
  return coordinateSpaceDimension;
}
