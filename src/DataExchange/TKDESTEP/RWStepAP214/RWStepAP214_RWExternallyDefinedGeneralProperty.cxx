#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWExternallyDefinedGeneralProperty.hpp"
#include <StepAP214_ExternallyDefinedGeneralProperty.hpp>
#include <StepBasic_ExternallyDefinedItem.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWExternallyDefinedGeneralProperty::RWStepAP214_RWExternallyDefinedGeneralProperty() =
  default;

void RWStepAP214_RWExternallyDefinedGeneralProperty::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepAP214_ExternallyDefinedGeneralProperty>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "externally_defined_general_property"))
    return;

  occ::handle<TCollection_HAsciiString> aGeneralProperty_Id;
  data->ReadString(num, 1, "general_property.id", ach, aGeneralProperty_Id);

  occ::handle<TCollection_HAsciiString> aGeneralProperty_Name;
  data->ReadString(num, 2, "general_property.name", ach, aGeneralProperty_Name);

  occ::handle<TCollection_HAsciiString> aGeneralProperty_Description;
  bool                                  hasGeneralProperty_Description = true;
  if (data->IsParamDefined(num, 3))
  {
    data->ReadString(num, 3, "general_property.description", ach, aGeneralProperty_Description);
  }
  else
  {
    hasGeneralProperty_Description = false;
  }

  StepBasic_SourceItem aExternallyDefinedItem_ItemId;
  data->ReadEntity(num, 4, "externally_defined_item.item_id", ach, aExternallyDefinedItem_ItemId);

  occ::handle<StepBasic_ExternalSource> aExternallyDefinedItem_Source;
  data->ReadEntity(num,
                   5,
                   "externally_defined_item.source",
                   ach,
                   STANDARD_TYPE(StepBasic_ExternalSource),
                   aExternallyDefinedItem_Source);

  ent->Init(aGeneralProperty_Id,
            aGeneralProperty_Name,
            hasGeneralProperty_Description,
            aGeneralProperty_Description,
            aExternallyDefinedItem_ItemId,
            aExternallyDefinedItem_Source);
}

void RWStepAP214_RWExternallyDefinedGeneralProperty::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepAP214_ExternallyDefinedGeneralProperty>& ent) const
{

  SW.Send(ent->StepBasic_GeneralProperty::Id());

  SW.Send(ent->StepBasic_GeneralProperty::Name());

  if (ent->StepBasic_GeneralProperty::HasDescription())
  {
    SW.Send(ent->StepBasic_GeneralProperty::Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->ExternallyDefinedItem()->ItemId().Value());

  SW.Send(ent->ExternallyDefinedItem()->Source());
}

void RWStepAP214_RWExternallyDefinedGeneralProperty::Share(
  const occ::handle<StepAP214_ExternallyDefinedGeneralProperty>& ent,
  Interface_EntityIterator&                                      iter) const
{

  iter.AddItem(ent->ExternallyDefinedItem()->ItemId().Value());

  iter.AddItem(ent->ExternallyDefinedItem()->Source());
}
