

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWPresentationLayerAssignment.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PresentationLayerAssignment.hpp>

RWStepVisual_RWPresentationLayerAssignment::RWStepVisual_RWPresentationLayerAssignment() = default;

void RWStepVisual_RWPresentationLayerAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&                data,
  const int                                                  num,
  occ::handle<Interface_Check>&                              ach,
  const occ::handle<StepVisual_PresentationLayerAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "presentation_layer_assignment"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;

  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<NCollection_HArray1<StepVisual_LayeredItem>> aAssignedItems;
  StepVisual_LayeredItem                                   aAssignedItemsItem;
  int                                                      nsub3;
  if (data->ReadSubList(num, 3, "assigned_items", ach, nsub3))
  {
    int nb3 = data->NbParams(nsub3);
    if (nb3 > 0)
    {
      aAssignedItems = new NCollection_HArray1<StepVisual_LayeredItem>(1, nb3);
      for (int i3 = 1; i3 <= nb3; i3++)
      {

        if (data->ReadEntity(nsub3, i3, "assigned_items", ach, aAssignedItemsItem))
          aAssignedItems->SetValue(i3, aAssignedItemsItem);
      }
    }
  }

  ent->Init(aName, aDescription, aAssignedItems);
}

void RWStepVisual_RWPresentationLayerAssignment::WriteStep(
  StepData_StepWriter&                                       SW,
  const occ::handle<StepVisual_PresentationLayerAssignment>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbAssignedItems(); i3++)
  {
    SW.Send(ent->AssignedItemsValue(i3).Value());
  }
  SW.CloseSub();
}

void RWStepVisual_RWPresentationLayerAssignment::Share(
  const occ::handle<StepVisual_PresentationLayerAssignment>& ent,
  Interface_EntityIterator&                                  iter) const
{

  int nbElem1 = ent->NbAssignedItems();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->AssignedItemsValue(is1).Value());
  }
}
