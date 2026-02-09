

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAutoDesignPresentedItem.hpp"
#include <StepAP214_AutoDesignPresentedItem.hpp>
#include <StepAP214_AutoDesignPresentedItemSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAutoDesignPresentedItem::RWStepAP214_RWAutoDesignPresentedItem() = default;

void RWStepAP214_RWAutoDesignPresentedItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepAP214_AutoDesignPresentedItem>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "auto_design_presented_item"))
    return;

  occ::handle<NCollection_HArray1<StepAP214_AutoDesignPresentedItemSelect>> aItems;
  StepAP214_AutoDesignPresentedItemSelect                                   anent1;
  int                                                                       nsub1;
  if (data->ReadSubList(num, 1, "items", ach, nsub1))
  {
    int nb1 = data->NbParams(nsub1);
    aItems  = new NCollection_HArray1<StepAP214_AutoDesignPresentedItemSelect>(1, nb1);
    for (int i1 = 1; i1 <= nb1; i1++)
    {
      bool stat1 = data->ReadEntity(nsub1, i1, "auto_design_displayed_item", ach, anent1);
      if (stat1)
        aItems->SetValue(i1, anent1);
    }
  }

  ent->Init(aItems);
}

void RWStepAP214_RWAutoDesignPresentedItem::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepAP214_AutoDesignPresentedItem>& ent) const
{

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->NbItems(); i1++)
  {
    SW.Send(ent->ItemsValue(i1).Value());
  }
  SW.CloseSub();
}

void RWStepAP214_RWAutoDesignPresentedItem::Share(
  const occ::handle<StepAP214_AutoDesignPresentedItem>& ent,
  Interface_EntityIterator&                             iter) const
{

  int nbElem1 = ent->NbItems();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ItemsValue(is1).Value());
  }
}
