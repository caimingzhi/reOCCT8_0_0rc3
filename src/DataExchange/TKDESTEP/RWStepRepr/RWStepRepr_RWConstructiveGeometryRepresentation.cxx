#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWConstructiveGeometryRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_ConstructiveGeometryRepresentation.hpp>

RWStepRepr_RWConstructiveGeometryRepresentation::RWStepRepr_RWConstructiveGeometryRepresentation() =
  default;

void RWStepRepr_RWConstructiveGeometryRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                     data,
  const int                                                       num,
  occ::handle<Interface_Check>&                                   ach,
  const occ::handle<StepRepr_ConstructiveGeometryRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "constructive_geometry_representation"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems;
  occ::handle<StepRepr_RepresentationItem>                                   anEnt;
  int                                                                        nsub;
  if (data->ReadSubList(num, 2, "items", ach, nsub))
  {
    int nb = data->NbParams(nsub);
    aItems = new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nb);
    for (int i = 1; i <= nb; i++)
    {
      if (data->ReadEntity(nsub,
                           i,
                           "representation_item",
                           ach,
                           STANDARD_TYPE(StepRepr_RepresentationItem),
                           anEnt))
        aItems->SetValue(i, anEnt);
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

void RWStepRepr_RWConstructiveGeometryRepresentation::WriteStep(
  StepData_StepWriter&                                            SW,
  const occ::handle<StepRepr_ConstructiveGeometryRepresentation>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i = 1; i <= ent->NbItems(); i++)
  {
    SW.Send(ent->ItemsValue(i));
  }
  SW.CloseSub();

  SW.Send(ent->ContextOfItems());
}

void RWStepRepr_RWConstructiveGeometryRepresentation::Share(
  const occ::handle<StepRepr_ConstructiveGeometryRepresentation>& ent,
  Interface_EntityIterator&                                       iter) const
{
  int nbElem = ent->NbItems();
  for (int i = 1; i <= nbElem; i++)
  {
    iter.GetOneItem(ent->ItemsValue(i));
  }
  iter.GetOneItem(ent->ContextOfItems());
}
