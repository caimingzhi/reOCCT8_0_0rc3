

#include "RWStepRepr_RWRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_RepresentationItem.hpp>

RWStepRepr_RWRepresentationItem::RWStepRepr_RWRepresentationItem() = default;

void RWStepRepr_RWRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepRepr_RepresentationItem>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepRepr_RWRepresentationItem::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepRepr_RepresentationItem>& ent) const
{

  SW.Send(ent->Name());
}
