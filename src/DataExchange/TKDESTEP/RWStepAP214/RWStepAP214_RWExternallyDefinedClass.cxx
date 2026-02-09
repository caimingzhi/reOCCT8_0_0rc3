#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWExternallyDefinedClass.hpp"
#include <StepAP214_ExternallyDefinedClass.hpp>
#include <StepBasic_ExternallyDefinedItem.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWExternallyDefinedClass::RWStepAP214_RWExternallyDefinedClass() = default;

void RWStepAP214_RWExternallyDefinedClass::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepAP214_ExternallyDefinedClass>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "externally_defined_class"))
    return;

  occ::handle<TCollection_HAsciiString> aGroup_Name;
  data->ReadString(num, 1, "group.name", ach, aGroup_Name);

  occ::handle<TCollection_HAsciiString> aGroup_Description;
  bool                                  hasGroup_Description = true;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "group.description", ach, aGroup_Description);
  }
  else
  {
    hasGroup_Description = false;
  }

  StepBasic_SourceItem aExternallyDefinedItem_ItemId;
  data->ReadEntity(num, 3, "externally_defined_item.item_id", ach, aExternallyDefinedItem_ItemId);

  occ::handle<StepBasic_ExternalSource> aExternallyDefinedItem_Source;
  data->ReadEntity(num,
                   4,
                   "externally_defined_item.source",
                   ach,
                   STANDARD_TYPE(StepBasic_ExternalSource),
                   aExternallyDefinedItem_Source);

  ent->Init(aGroup_Name,
            hasGroup_Description,
            aGroup_Description,
            aExternallyDefinedItem_ItemId,
            aExternallyDefinedItem_Source);
}

void RWStepAP214_RWExternallyDefinedClass::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepAP214_ExternallyDefinedClass>& ent) const
{

  SW.Send(ent->StepBasic_Group::Name());

  if (ent->StepBasic_Group::HasDescription())
  {
    SW.Send(ent->StepBasic_Group::Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->ExternallyDefinedItem()->ItemId().Value());

  SW.Send(ent->ExternallyDefinedItem()->Source());
}

void RWStepAP214_RWExternallyDefinedClass::Share(
  const occ::handle<StepAP214_ExternallyDefinedClass>& ent,
  Interface_EntityIterator&                            iter) const
{

  iter.AddItem(ent->ExternallyDefinedItem()->ItemId().Value());

  iter.AddItem(ent->ExternallyDefinedItem()->Source());
}
