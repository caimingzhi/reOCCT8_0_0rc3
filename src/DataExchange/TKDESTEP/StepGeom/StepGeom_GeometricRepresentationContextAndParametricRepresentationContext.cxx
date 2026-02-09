

#include <Standard_Type.hpp>
#include <StepGeom_GeometricRepresentationContext.hpp>
#include <StepGeom_GeometricRepresentationContextAndParametricRepresentationContext.hpp>
#include <StepRepr_GlobalUnitAssignedContext.hpp>
#include <StepRepr_ParametricRepresentationContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(
  StepGeom_GeometricRepresentationContextAndParametricRepresentationContext,
  StepRepr_RepresentationContext)

StepGeom_GeometricRepresentationContextAndParametricRepresentationContext::
  StepGeom_GeometricRepresentationContextAndParametricRepresentationContext() = default;

void StepGeom_GeometricRepresentationContextAndParametricRepresentationContext::Init(
  const occ::handle<TCollection_HAsciiString>&                 aContextIdentifier,
  const occ::handle<TCollection_HAsciiString>&                 aContextType,
  const occ::handle<StepGeom_GeometricRepresentationContext>&  aGeometricRepresentationContext,
  const occ::handle<StepRepr_ParametricRepresentationContext>& aParametricRepresentationContext)
{

  geometricRepresentationContext  = aGeometricRepresentationContext;
  parametricRepresentationContext = aParametricRepresentationContext;

  StepRepr_RepresentationContext::Init(aContextIdentifier, aContextType);
}

void StepGeom_GeometricRepresentationContextAndParametricRepresentationContext::Init(
  const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
  const occ::handle<TCollection_HAsciiString>& aContextType,
  const int                                    aCoordinateSpaceDimension)
{

  StepRepr_RepresentationContext::Init(aContextIdentifier, aContextType);

  geometricRepresentationContext = new StepGeom_GeometricRepresentationContext();
  geometricRepresentationContext->Init(aContextIdentifier, aContextType, aCoordinateSpaceDimension);

  parametricRepresentationContext = new StepRepr_ParametricRepresentationContext();
  parametricRepresentationContext->Init(aContextIdentifier, aContextType);
}

void StepGeom_GeometricRepresentationContextAndParametricRepresentationContext::
  SetGeometricRepresentationContext(
    const occ::handle<StepGeom_GeometricRepresentationContext>& aGeometricRepresentationContext)
{
  geometricRepresentationContext = aGeometricRepresentationContext;
}

occ::handle<StepGeom_GeometricRepresentationContext>
  StepGeom_GeometricRepresentationContextAndParametricRepresentationContext::
    GeometricRepresentationContext() const
{
  return geometricRepresentationContext;
}

void StepGeom_GeometricRepresentationContextAndParametricRepresentationContext::
  SetParametricRepresentationContext(
    const occ::handle<StepRepr_ParametricRepresentationContext>& aParametricRepresentationContext)
{
  parametricRepresentationContext = aParametricRepresentationContext;
}

occ::handle<StepRepr_ParametricRepresentationContext>
  StepGeom_GeometricRepresentationContextAndParametricRepresentationContext::
    ParametricRepresentationContext() const
{
  return parametricRepresentationContext;
}

void StepGeom_GeometricRepresentationContextAndParametricRepresentationContext::
  SetCoordinateSpaceDimension(const int aCoordinateSpaceDimension)
{
  geometricRepresentationContext->SetCoordinateSpaceDimension(aCoordinateSpaceDimension);
}

int StepGeom_GeometricRepresentationContextAndParametricRepresentationContext::
  CoordinateSpaceDimension() const
{
  return geometricRepresentationContext->CoordinateSpaceDimension();
}
