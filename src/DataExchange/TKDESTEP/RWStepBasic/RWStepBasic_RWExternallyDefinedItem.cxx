#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWExternallyDefinedItem.hpp"
#include <StepBasic_ExternallyDefinedItem.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWExternallyDefinedItem::RWStepBasic_RWExternallyDefinedItem() = default;

void RWStepBasic_RWExternallyDefinedItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepBasic_ExternallyDefinedItem>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "externally_defined_item"))
    return;

  StepBasic_SourceItem aItemId;
  data->ReadEntity(num, 1, "item_id", ach, aItemId);

  occ::handle<StepBasic_ExternalSource> aSource;
  data->ReadEntity(num, 2, "source", ach, STANDARD_TYPE(StepBasic_ExternalSource), aSource);

  ent->Init(aItemId, aSource);
}

void RWStepBasic_RWExternallyDefinedItem::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepBasic_ExternallyDefinedItem>& ent) const
{

  SW.Send(ent->ItemId().Value());

  SW.Send(ent->Source());
}

void RWStepBasic_RWExternallyDefinedItem::Share(
  const occ::handle<StepBasic_ExternallyDefinedItem>& ent,
  Interface_EntityIterator&                           iter) const
{

  iter.AddItem(ent->ItemId().Value());

  iter.AddItem(ent->Source());
}
