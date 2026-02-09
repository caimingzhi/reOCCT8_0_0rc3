

#include "RWStepGeom_RWGeometricRepresentationContext.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_GeometricRepresentationContext.hpp>

RWStepGeom_RWGeometricRepresentationContext::RWStepGeom_RWGeometricRepresentationContext() =
  default;

void RWStepGeom_RWGeometricRepresentationContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepGeom_GeometricRepresentationContext>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "geometric_representation_context"))
    return;

  occ::handle<TCollection_HAsciiString> aContextIdentifier;

  data->ReadString(num, 1, "context_identifier", ach, aContextIdentifier);

  occ::handle<TCollection_HAsciiString> aContextType;

  data->ReadString(num, 2, "context_type", ach, aContextType);

  int aCoordinateSpaceDimension;

  data->ReadInteger(num, 3, "coordinate_space_dimension", ach, aCoordinateSpaceDimension);

  ent->Init(aContextIdentifier, aContextType, aCoordinateSpaceDimension);
}

void RWStepGeom_RWGeometricRepresentationContext::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepGeom_GeometricRepresentationContext>& ent) const
{

  SW.Send(ent->ContextIdentifier());

  SW.Send(ent->ContextType());

  SW.Send(ent->CoordinateSpaceDimension());
}
