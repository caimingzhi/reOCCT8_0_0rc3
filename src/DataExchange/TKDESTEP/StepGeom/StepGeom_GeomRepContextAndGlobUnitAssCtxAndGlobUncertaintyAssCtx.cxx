#include <Standard_Type.hpp>
#include <StepGeom_GeometricRepresentationContext.hpp>
#include <StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.hpp>
#include <StepRepr_GlobalUncertaintyAssignedContext.hpp>
#include <StepRepr_GlobalUnitAssignedContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx,
                           StepRepr_RepresentationContext)

StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::
  StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx() = default;

void StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::Init(
  const occ::handle<TCollection_HAsciiString>&                  aContextIdentifier,
  const occ::handle<TCollection_HAsciiString>&                  aContextType,
  const occ::handle<StepGeom_GeometricRepresentationContext>&   aGeometricRepresentationContext,
  const occ::handle<StepRepr_GlobalUnitAssignedContext>&        aGlobalUnitAssignedContext,
  const occ::handle<StepRepr_GlobalUncertaintyAssignedContext>& aGlobalUncertaintyAssignedCtx)
{

  geometricRepresentationContext   = aGeometricRepresentationContext;
  globalUnitAssignedContext        = aGlobalUnitAssignedContext;
  globalUncertaintyAssignedContext = aGlobalUncertaintyAssignedCtx;

  StepRepr_RepresentationContext::Init(aContextIdentifier, aContextType);
}

void StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::Init(
  const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
  const occ::handle<TCollection_HAsciiString>& aContextType,
  const int                                    aCoordinateSpaceDimension,
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits,
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>&
    anUncertainty)
{

  StepRepr_RepresentationContext::Init(aContextIdentifier, aContextType);

  geometricRepresentationContext = new StepGeom_GeometricRepresentationContext();
  geometricRepresentationContext->Init(aContextIdentifier, aContextType, aCoordinateSpaceDimension);

  globalUnitAssignedContext = new StepRepr_GlobalUnitAssignedContext();
  globalUnitAssignedContext->Init(aContextIdentifier, aContextType, aUnits);

  globalUncertaintyAssignedContext = new StepRepr_GlobalUncertaintyAssignedContext();
  globalUncertaintyAssignedContext->Init(aContextIdentifier, aContextType, anUncertainty);
}

void StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::
  SetGeometricRepresentationContext(
    const occ::handle<StepGeom_GeometricRepresentationContext>& aGeometricRepresentationContext)
{
  geometricRepresentationContext = aGeometricRepresentationContext;
}

occ::handle<StepGeom_GeometricRepresentationContext>
  StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::GeometricRepresentationContext()
    const
{
  return geometricRepresentationContext;
}

void StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::SetGlobalUnitAssignedContext(
  const occ::handle<StepRepr_GlobalUnitAssignedContext>& aGlobalUnitAssignedContext)
{
  globalUnitAssignedContext = aGlobalUnitAssignedContext;
}

occ::handle<StepRepr_GlobalUnitAssignedContext>
  StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::GlobalUnitAssignedContext()
    const
{
  return globalUnitAssignedContext;
}

void StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::
  SetGlobalUncertaintyAssignedContext(
    const occ::handle<StepRepr_GlobalUncertaintyAssignedContext>& aGlobalUncertaintyAssignedCtx)
{
  globalUncertaintyAssignedContext = aGlobalUncertaintyAssignedCtx;
}

occ::handle<StepRepr_GlobalUncertaintyAssignedContext>
  StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::
    GlobalUncertaintyAssignedContext() const
{
  return globalUncertaintyAssignedContext;
}

void StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::SetCoordinateSpaceDimension(
  const int aCoordinateSpaceDimension)
{
  geometricRepresentationContext->SetCoordinateSpaceDimension(aCoordinateSpaceDimension);
}

int StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::CoordinateSpaceDimension()
  const
{
  return geometricRepresentationContext->CoordinateSpaceDimension();
}

void StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::SetUnits(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits)
{
  globalUnitAssignedContext->SetUnits(aUnits);
}

occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>
  StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::Units() const
{
  return globalUnitAssignedContext->Units();
}

occ::handle<StepBasic_NamedUnit> StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::
  UnitsValue(const int num) const
{
  return globalUnitAssignedContext->UnitsValue(num);
}

int StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::NbUnits() const
{
  return globalUnitAssignedContext->NbUnits();
}

void StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::SetUncertainty(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>&
    aUncertainty)
{
  globalUncertaintyAssignedContext->SetUncertainty(aUncertainty);
}

occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>
  StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::Uncertainty() const
{
  return globalUncertaintyAssignedContext->Uncertainty();
}

occ::handle<StepBasic_UncertaintyMeasureWithUnit>
  StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::UncertaintyValue(
    const int num) const
{
  return globalUncertaintyAssignedContext->UncertaintyValue(num);
}

int StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx::NbUncertainty() const
{
  return globalUncertaintyAssignedContext->NbUncertainty();
}
