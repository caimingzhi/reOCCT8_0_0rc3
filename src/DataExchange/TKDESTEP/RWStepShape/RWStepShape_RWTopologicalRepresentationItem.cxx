

#include "RWStepShape_RWTopologicalRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>

RWStepShape_RWTopologicalRepresentationItem::RWStepShape_RWTopologicalRepresentationItem() =
  default;

void RWStepShape_RWTopologicalRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepShape_TopologicalRepresentationItem>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "topological_representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepShape_RWTopologicalRepresentationItem::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepShape_TopologicalRepresentationItem>& ent) const
{

  SW.Send(ent->Name());
}
