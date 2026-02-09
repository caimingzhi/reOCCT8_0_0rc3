#include "RWStepAP242_RWItemIdentifiedRepresentationUsage.hpp"
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepAP242_ItemIdentifiedRepresentationUsage.hpp>
#include <StepAP242_ItemIdentifiedRepresentationUsageDefinition.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>

RWStepAP242_RWItemIdentifiedRepresentationUsage::RWStepAP242_RWItemIdentifiedRepresentationUsage() =
  default;

void RWStepAP242_RWItemIdentifiedRepresentationUsage::ReadStep(
  const occ::handle<StepData_StepReaderData>&                     data,
  const int                                                       num,
  occ::handle<Interface_Check>&                                   ach,
  const occ::handle<StepAP242_ItemIdentifiedRepresentationUsage>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "item_identified_representation_usage"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "description", ach, aDescription);
  }

  StepAP242_ItemIdentifiedRepresentationUsageDefinition aDefinition;
  data->ReadEntity(num, 3, "definition", ach, aDefinition);

  occ::handle<StepRepr_Representation> aRepresentation;
  data->ReadEntity(num,
                   4,
                   "used_representation",
                   ach,
                   STANDARD_TYPE(StepRepr_Representation),
                   aRepresentation);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> anItems;
  occ::handle<StepRepr_RepresentationItem>                                   anEnt;
  int                                                                        nbSub;
  Interface_ParamType aType = data->ParamType(num, 5);
  if (aType == Interface_ParamIdent)
  {
    data->ReadEntity(num,
                     5,
                     "item_identified_representation_usage.identified_item",
                     ach,
                     STANDARD_TYPE(StepRepr_RepresentationItem),
                     anEnt);
    anItems = new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
    anItems->SetValue(1, anEnt);
  }
  else if (data->ReadSubList(num,
                             5,
                             "item_identified_representation_usage.identified_item",
                             ach,
                             nbSub))
  {
    int nbElements = data->NbParams(nbSub);
    anItems = new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nbElements);
    for (int i = 1; i <= nbElements; i++)
    {
      if (data->ReadEntity(nbSub,
                           i,
                           "representation_item",
                           ach,
                           STANDARD_TYPE(StepRepr_RepresentationItem),
                           anEnt))
        anItems->SetValue(i, anEnt);
    }
  }

  ent->Init(aName, aDescription, aDefinition, aRepresentation, anItems);
}

void RWStepAP242_RWItemIdentifiedRepresentationUsage::WriteStep(
  StepData_StepWriter&                                            SW,
  const occ::handle<StepAP242_ItemIdentifiedRepresentationUsage>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->Definition().Value());

  SW.Send(ent->UsedRepresentation());

  if (ent->NbIdentifiedItem() == 1)
    SW.Send(ent->IdentifiedItemValue(1));
  else
  {
    SW.OpenSub();
    for (int i = 1; i <= ent->NbIdentifiedItem(); i++)
    {
      SW.Send(ent->IdentifiedItemValue(i));
    }
    SW.CloseSub();
  }
}

void RWStepAP242_RWItemIdentifiedRepresentationUsage::Share(
  const occ::handle<StepAP242_ItemIdentifiedRepresentationUsage>& ent,
  Interface_EntityIterator&                                       iter) const
{
  iter.AddItem(ent->Definition().Value());
  int i, nb = ent->NbIdentifiedItem();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->IdentifiedItemValue(i));
}
