

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWInvisibility.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_Invisibility.hpp>
#include <StepVisual_InvisibleItem.hpp>

RWStepVisual_RWInvisibility::RWStepVisual_RWInvisibility() = default;

void RWStepVisual_RWInvisibility::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepVisual_Invisibility>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "invisibility"))
    return;

  occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>> aInvisibleItems;
  StepVisual_InvisibleItem                                   aInvisibleItemsItem;
  int                                                        nsub1;
  if (data->ReadSubList(num, 1, "invisible_items", ach, nsub1))
  {
    int nb1         = data->NbParams(nsub1);
    aInvisibleItems = new NCollection_HArray1<StepVisual_InvisibleItem>(1, nb1);
    for (int i1 = 1; i1 <= nb1; i1++)
    {

      if (data->ReadEntity(nsub1, i1, "invisible_items", ach, aInvisibleItemsItem))
        aInvisibleItems->SetValue(i1, aInvisibleItemsItem);
    }
  }

  ent->Init(aInvisibleItems);
}

void RWStepVisual_RWInvisibility::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepVisual_Invisibility>& ent) const
{

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->NbInvisibleItems(); i1++)
  {
    SW.Send(ent->InvisibleItemsValue(i1).Value());
  }
  SW.CloseSub();
}

void RWStepVisual_RWInvisibility::Share(const occ::handle<StepVisual_Invisibility>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  int nbElem1 = ent->NbInvisibleItems();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->InvisibleItemsValue(is1).Value());
  }
}
