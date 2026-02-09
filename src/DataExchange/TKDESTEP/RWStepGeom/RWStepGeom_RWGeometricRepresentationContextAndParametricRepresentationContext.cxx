

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_GeometricRepresentationContextAndParametricRepresentationContext.hpp>

RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::
  RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext() = default;

void RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::ReadStep(
  const occ::handle<StepData_StepReaderData>& data,
  const int                                   num0,
  occ::handle<Interface_Check>&               ach,
  const occ::handle<StepGeom_GeometricRepresentationContextAndParametricRepresentationContext>& ent)
  const
{

  int num = num0;

  if (!data->CheckNbParams(num, 1, ach, "geometric_representation_context"))
    return;

  int aCoordinateSpaceDimension;

  data->ReadInteger(num, 1, "coordinate_space_dimension", ach, aCoordinateSpaceDimension);

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "parametric_representation_context"))
    return;

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 2, ach, "representation_context"))
    return;

  occ::handle<TCollection_HAsciiString> aContextIdentifier;

  data->ReadString(num, 1, "context_identifier", ach, aContextIdentifier);

  occ::handle<TCollection_HAsciiString> aContextType;

  data->ReadString(num, 2, "context_type", ach, aContextType);

  ent->Init(aContextIdentifier, aContextType, aCoordinateSpaceDimension);
}

void RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::WriteStep(
  StepData_StepWriter&                                                                          SW,
  const occ::handle<StepGeom_GeometricRepresentationContextAndParametricRepresentationContext>& ent)
  const
{

  SW.StartEntity("GEOMETRIC_REPRESENTATION_CONTEXT");

  SW.Send(ent->CoordinateSpaceDimension());

  SW.StartEntity("PARAMETRIC_REPRESENTATION_CONTEXT");

  SW.StartEntity("REPRESENTATION_CONTEXT");

  SW.Send(ent->ContextIdentifier());

  SW.Send(ent->ContextType());
}

void RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext::Share(
  const occ::handle<StepGeom_GeometricRepresentationContextAndParametricRepresentationContext>&,
  Interface_EntityIterator&) const
{
}
