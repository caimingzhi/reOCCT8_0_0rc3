

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAutoDesignNominalDateAssignment.hpp"
#include <StepAP214_AutoDesignNominalDateAssignment.hpp>
#include <StepAP214_AutoDesignDatedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Date.hpp>
#include <StepBasic_DateRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAutoDesignNominalDateAssignment::RWStepAP214_RWAutoDesignNominalDateAssignment() =
  default;

void RWStepAP214_RWAutoDesignNominalDateAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   data,
  const int                                                     num,
  occ::handle<Interface_Check>&                                 ach,
  const occ::handle<StepAP214_AutoDesignNominalDateAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "auto_design_nominal_date_assignment"))
    return;

  occ::handle<StepBasic_Date> aAssignedDate;
  data->ReadEntity(num, 1, "assigned_date", ach, STANDARD_TYPE(StepBasic_Date), aAssignedDate);

  occ::handle<StepBasic_DateRole> aRole;
  data->ReadEntity(num, 2, "role", ach, STANDARD_TYPE(StepBasic_DateRole), aRole);

  occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>> aItems;
  StepAP214_AutoDesignDatedItem                                   aItemsItem;
  int                                                             nsub3;
  if (data->ReadSubList(num, 3, "items", ach, nsub3))
  {
    int nb3 = data->NbParams(nsub3);
    aItems  = new NCollection_HArray1<StepAP214_AutoDesignDatedItem>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {
      bool stat3 = data->ReadEntity(nsub3, i3, "items", ach, aItemsItem);
      if (stat3)
        aItems->SetValue(i3, aItemsItem);
    }
  }

  ent->Init(aAssignedDate, aRole, aItems);
}

void RWStepAP214_RWAutoDesignNominalDateAssignment::WriteStep(
  StepData_StepWriter&                                          SW,
  const occ::handle<StepAP214_AutoDesignNominalDateAssignment>& ent) const
{

  SW.Send(ent->AssignedDate());

  SW.Send(ent->Role());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbItems(); i3++)
  {
    SW.Send(ent->ItemsValue(i3).Value());
  }
  SW.CloseSub();
}

void RWStepAP214_RWAutoDesignNominalDateAssignment::Share(
  const occ::handle<StepAP214_AutoDesignNominalDateAssignment>& ent,
  Interface_EntityIterator&                                     iter) const
{

  iter.GetOneItem(ent->AssignedDate());

  iter.GetOneItem(ent->Role());

  int nbElem3 = ent->NbItems();
  for (int is3 = 1; is3 <= nbElem3; is3++)
  {
    iter.GetOneItem(ent->ItemsValue(is3).Value());
  }
}
