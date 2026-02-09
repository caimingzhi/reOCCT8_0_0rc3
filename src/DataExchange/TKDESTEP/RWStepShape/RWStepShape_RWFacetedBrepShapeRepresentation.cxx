

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWFacetedBrepShapeRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepShape_FacetedBrepShapeRepresentation.hpp>

RWStepShape_RWFacetedBrepShapeRepresentation::RWStepShape_RWFacetedBrepShapeRepresentation() =
  default;

void RWStepShape_RWFacetedBrepShapeRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                  data,
  const int                                                    num,
  occ::handle<Interface_Check>&                                ach,
  const occ::handle<StepShape_FacetedBrepShapeRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "faceted_brep_shape_representation"))
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

void RWStepShape_RWFacetedBrepShapeRepresentation::WriteStep(
  StepData_StepWriter&                                         SW,
  const occ::handle<StepShape_FacetedBrepShapeRepresentation>& ent) const
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

void RWStepShape_RWFacetedBrepShapeRepresentation::Share(
  const occ::handle<StepShape_FacetedBrepShapeRepresentation>& ent,
  Interface_EntityIterator&                                    iter) const
{

  int nbElem1 = ent->NbItems();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ItemsValue(is1));
  }

  iter.GetOneItem(ent->ContextOfItems());
}
