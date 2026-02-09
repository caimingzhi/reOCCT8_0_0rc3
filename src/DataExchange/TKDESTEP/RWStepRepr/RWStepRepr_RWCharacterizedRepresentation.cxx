#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWCharacterizedRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_CharacterizedRepresentation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_RepresentationItem.hpp>

RWStepRepr_RWCharacterizedRepresentation::RWStepRepr_RWCharacterizedRepresentation() = default;

void RWStepRepr_RWCharacterizedRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepRepr_CharacterizedRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "characterized_representation"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> anItems;
  occ::handle<StepRepr_RepresentationItem>                                   anItem;
  int                                                                        nsub;
  if (data->ReadSubList(num, 3, "items", ach, nsub))
  {
    int nb  = data->NbParams(nsub);
    anItems = new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nb);
    for (int i = 1; i <= nb; i++)
    {
      if (data->ReadEntity(nsub,
                           i,
                           "representation_item",
                           ach,
                           STANDARD_TYPE(StepRepr_RepresentationItem),
                           anItem))
        anItems->SetValue(i, anItem);
    }
  }

  occ::handle<StepRepr_RepresentationContext> aContextOfItems;
  data->ReadEntity(num,
                   4,
                   "context_of_items",
                   ach,
                   STANDARD_TYPE(StepRepr_RepresentationContext),
                   aContextOfItems);

  ent->Init(aName, aDescription, anItems, aContextOfItems);
}

void RWStepRepr_RWCharacterizedRepresentation::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepRepr_CharacterizedRepresentation>& ent) const
{

  SW.Send(ent->Name());

  if (!ent->Description().IsNull())
    SW.Send(ent->Description());
  else
    SW.SendUndef();

  SW.OpenSub();
  for (int i = 1; i <= ent->NbItems(); i++)
  {
    SW.Send(ent->ItemsValue(i));
  }
  SW.CloseSub();

  SW.Send(ent->ContextOfItems());
}

void RWStepRepr_RWCharacterizedRepresentation::Share(
  const occ::handle<StepRepr_CharacterizedRepresentation>& ent,
  Interface_EntityIterator&                                iter) const
{
  int nbElem = ent->NbItems();
  for (int i = 1; i <= nbElem; i++)
  {
    iter.GetOneItem(ent->ItemsValue(i));
  }
  iter.GetOneItem(ent->ContextOfItems());
}
