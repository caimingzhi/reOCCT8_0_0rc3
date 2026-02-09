#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWConfigurationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ConfigurationItem.hpp>
#include <StepRepr_ProductConcept.hpp>

RWStepRepr_RWConfigurationItem::RWStepRepr_RWConfigurationItem() = default;

void RWStepRepr_RWConfigurationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepRepr_ConfigurationItem>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "configuration_item"))
    return;

  occ::handle<TCollection_HAsciiString> aId;
  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 2, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 3))
  {
    data->ReadString(num, 3, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  occ::handle<StepRepr_ProductConcept> aItemConcept;
  data
    ->ReadEntity(num, 4, "item_concept", ach, STANDARD_TYPE(StepRepr_ProductConcept), aItemConcept);

  occ::handle<TCollection_HAsciiString> aPurpose;
  bool                                  hasPurpose = true;
  if (data->IsParamDefined(num, 5))
  {
    data->ReadString(num, 5, "purpose", ach, aPurpose);
  }
  else
  {
    hasPurpose = false;
  }

  ent->Init(aId, aName, hasDescription, aDescription, aItemConcept, hasPurpose, aPurpose);
}

void RWStepRepr_RWConfigurationItem::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepRepr_ConfigurationItem>& ent) const
{

  SW.Send(ent->Id());

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->ItemConcept());

  if (ent->HasPurpose())
  {
    SW.Send(ent->Purpose());
  }
  else
    SW.SendUndef();
}

void RWStepRepr_RWConfigurationItem::Share(const occ::handle<StepRepr_ConfigurationItem>& ent,
                                           Interface_EntityIterator& iter) const
{

  iter.AddItem(ent->ItemConcept());
}
