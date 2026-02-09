

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAppliedPresentedItem.hpp"
#include <StepAP214_AppliedPresentedItem.hpp>
#include <StepAP214_PresentedItemSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAppliedPresentedItem::RWStepAP214_RWAppliedPresentedItem() = default;

void RWStepAP214_RWAppliedPresentedItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepAP214_AppliedPresentedItem>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "applied_presented_item"))
    return;

  occ::handle<NCollection_HArray1<StepAP214_PresentedItemSelect>> aItems;
  StepAP214_PresentedItemSelect                                   anent1;
  int                                                             nsub1;
  if (data->ReadSubList(num, 1, "items", ach, nsub1))
  {
    int nb1 = data->NbParams(nsub1);
    aItems  = new NCollection_HArray1<StepAP214_PresentedItemSelect>(1, nb1);
    for (int i1 = 1; i1 <= nb1; i1++)
    {
      bool stat1 = data->ReadEntity(nsub1, i1, "items", ach, anent1);
      if (stat1)
        aItems->SetValue(i1, anent1);
    }
  }

  ent->Init(aItems);
}

void RWStepAP214_RWAppliedPresentedItem::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepAP214_AppliedPresentedItem>& ent) const
{

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->NbItems(); i1++)
  {
    SW.Send(ent->ItemsValue(i1).Value());
  }
  SW.CloseSub();
}

void RWStepAP214_RWAppliedPresentedItem::Share(
  const occ::handle<StepAP214_AppliedPresentedItem>& ent,
  Interface_EntityIterator&                          iter) const
{

  int nbElem1 = ent->NbItems();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ItemsValue(is1).Value());
  }
}
