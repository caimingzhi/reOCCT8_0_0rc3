

#include "RWStepVisual_RWTessellatedItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_TessellatedItem.hpp>

RWStepVisual_RWTessellatedItem::RWStepVisual_RWTessellatedItem() = default;

void RWStepVisual_RWTessellatedItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepVisual_TessellatedItem>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "tessellated_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepVisual_RWTessellatedItem::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepVisual_TessellatedItem>& ent) const
{

  SW.Send(ent->Name());
}
