

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAutoDesignGroupAssignment.hpp"
#include <StepAP214_AutoDesignGroupAssignment.hpp>
#include <StepAP214_AutoDesignGroupedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Group.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAutoDesignGroupAssignment::RWStepAP214_RWAutoDesignGroupAssignment() = default;

void RWStepAP214_RWAutoDesignGroupAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&             data,
  const int                                               num,
  occ::handle<Interface_Check>&                           ach,
  const occ::handle<StepAP214_AutoDesignGroupAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "auto_design_group_assignment"))
    return;

  occ::handle<StepBasic_Group> aAssignedGroup;
  data->ReadEntity(num, 1, "assigned_group", ach, STANDARD_TYPE(StepBasic_Group), aAssignedGroup);

  occ::handle<NCollection_HArray1<StepAP214_AutoDesignGroupedItem>> aItems;
  StepAP214_AutoDesignGroupedItem                                   aItemsItem;
  int                                                               nsub2;
  if (data->ReadSubList(num, 2, "items", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aItems  = new NCollection_HArray1<StepAP214_AutoDesignGroupedItem>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {
      bool stat2 = data->ReadEntity(nsub2, i2, "items", ach, aItemsItem);
      if (stat2)
        aItems->SetValue(i2, aItemsItem);
    }
  }

  ent->Init(aAssignedGroup, aItems);
}

void RWStepAP214_RWAutoDesignGroupAssignment::WriteStep(
  StepData_StepWriter&                                    SW,
  const occ::handle<StepAP214_AutoDesignGroupAssignment>& ent) const
{

  SW.Send(ent->AssignedGroup());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbItems(); i2++)
  {
    SW.Send(ent->ItemsValue(i2).Value());
  }
  SW.CloseSub();
}

void RWStepAP214_RWAutoDesignGroupAssignment::Share(
  const occ::handle<StepAP214_AutoDesignGroupAssignment>& ent,
  Interface_EntityIterator&                               iter) const
{

  iter.GetOneItem(ent->AssignedGroup());

  int nbElem2 = ent->NbItems();
  for (int is2 = 1; is2 <= nbElem2; is2++)
  {
    iter.GetOneItem(ent->ItemsValue(is2).Value());
  }
}
