

#include "RWStepGeom_RWGeometricRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>

RWStepGeom_RWGeometricRepresentationItem::RWStepGeom_RWGeometricRepresentationItem() = default;

void RWStepGeom_RWGeometricRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepGeom_GeometricRepresentationItem>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "geometric_representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepGeom_RWGeometricRepresentationItem::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepGeom_GeometricRepresentationItem>& ent) const
{

  SW.Send(ent->Name());
}
