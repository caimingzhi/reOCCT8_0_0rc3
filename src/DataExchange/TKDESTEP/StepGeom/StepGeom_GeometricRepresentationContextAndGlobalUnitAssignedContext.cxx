

#include <Standard_Type.hpp>
#include <StepGeom_GeometricRepresentationContext.hpp>
#include <StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext.hpp>
#include <StepRepr_GlobalUnitAssignedContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext,
                           StepRepr_RepresentationContext)

StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::
  StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext() = default;

void StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::Init(
  const occ::handle<TCollection_HAsciiString>&                aContextIdentifier,
  const occ::handle<TCollection_HAsciiString>&                aContextType,
  const occ::handle<StepGeom_GeometricRepresentationContext>& aGeometricRepresentationContext,
  const occ::handle<StepRepr_GlobalUnitAssignedContext>&      aGlobalUnitAssignedContext)
{

  geometricRepresentationContext = aGeometricRepresentationContext;
  globalUnitAssignedContext      = aGlobalUnitAssignedContext;

  StepRepr_RepresentationContext::Init(aContextIdentifier, aContextType);
}

void StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::Init(
  const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
  const occ::handle<TCollection_HAsciiString>& aContextType,
  const int                                    aCoordinateSpaceDimension,
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits)
{

  StepRepr_RepresentationContext::Init(aContextIdentifier, aContextType);

  geometricRepresentationContext = new StepGeom_GeometricRepresentationContext();
  geometricRepresentationContext->Init(aContextIdentifier, aContextType, aCoordinateSpaceDimension);

  globalUnitAssignedContext = new StepRepr_GlobalUnitAssignedContext();
  globalUnitAssignedContext->Init(aContextIdentifier, aContextType, aUnits);
}

void StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::
  SetGeometricRepresentationContext(
    const occ::handle<StepGeom_GeometricRepresentationContext>& aGeometricRepresentationContext)
{
  geometricRepresentationContext = aGeometricRepresentationContext;
}

occ::handle<StepGeom_GeometricRepresentationContext>
  StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::
    GeometricRepresentationContext() const
{
  return geometricRepresentationContext;
}

void StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::
  SetGlobalUnitAssignedContext(
    const occ::handle<StepRepr_GlobalUnitAssignedContext>& aGlobalUnitAssignedContext)
{
  globalUnitAssignedContext = aGlobalUnitAssignedContext;
}

occ::handle<StepRepr_GlobalUnitAssignedContext>
  StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::GlobalUnitAssignedContext()
    const
{
  return globalUnitAssignedContext;
}

void StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::
  SetCoordinateSpaceDimension(const int aCoordinateSpaceDimension)
{
  geometricRepresentationContext->SetCoordinateSpaceDimension(aCoordinateSpaceDimension);
}

int StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::CoordinateSpaceDimension()
  const
{
  return geometricRepresentationContext->CoordinateSpaceDimension();
}

void StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::SetUnits(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits)
{
  globalUnitAssignedContext->SetUnits(aUnits);
}

occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>
  StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::Units() const
{
  return globalUnitAssignedContext->Units();
}

occ::handle<StepBasic_NamedUnit>
  StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::UnitsValue(
    const int num) const
{
  return globalUnitAssignedContext->UnitsValue(num);
}

int StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext::NbUnits() const
{
  return globalUnitAssignedContext->NbUnits();
}
