

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_RepresentationItem.hpp>

RWStepRepr_RWRepresentation::RWStepRepr_RWRepresentation() = default;

void RWStepRepr_RWRepresentation::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepRepr_Representation>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "representation"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems;
  occ::handle<StepRepr_RepresentationItem>                                   anent2;
  int                                                                        nsub2;
  if (data->ReadSubList(num, 2, "items", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aItems  = new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2,
                           i2,
                           "representation_item",
                           ach,
                           STANDARD_TYPE(StepRepr_RepresentationItem),
                           anent2))
        aItems->SetValue(i2, anent2);
    }
  }

  occ::handle<StepRepr_RepresentationContext> aContextOfItems;

  data->ReadEntity(num,
                   3,
                   "context_of_items",
                   ach,
                   STANDARD_TYPE(StepRepr_RepresentationContext),
                   aContextOfItems);

  ent->Init(aName, aItems, aContextOfItems);
}

void RWStepRepr_RWRepresentation::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepRepr_Representation>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbItems(); i2++)
  {
    SW.Send(ent->ItemsValue(i2));
  }
  SW.CloseSub();

  SW.Send(ent->ContextOfItems());
}

void RWStepRepr_RWRepresentation::Share(const occ::handle<StepRepr_Representation>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  int nbElem1 = ent->NbItems();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ItemsValue(is1));
  }

  iter.GetOneItem(ent->ContextOfItems());
}
