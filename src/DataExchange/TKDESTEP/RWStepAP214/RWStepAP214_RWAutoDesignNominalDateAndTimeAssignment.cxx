

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment.hpp"
#include <StepAP214_AutoDesignNominalDateAndTimeAssignment.hpp>
#include <StepAP214_AutoDesignDateAndTimeItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_DateTimeRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment::
  RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment() = default;

void RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&                          data,
  const int                                                            num,
  occ::handle<Interface_Check>&                                        ach,
  const occ::handle<StepAP214_AutoDesignNominalDateAndTimeAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "auto_design_nominal_date_and_time_assignment"))
    return;

  occ::handle<StepBasic_DateAndTime> aAssignedDateAndTime;
  data->ReadEntity(num,
                   1,
                   "assigned_date_and_time",
                   ach,
                   STANDARD_TYPE(StepBasic_DateAndTime),
                   aAssignedDateAndTime);

  occ::handle<StepBasic_DateTimeRole> aRole;
  data->ReadEntity(num, 2, "role", ach, STANDARD_TYPE(StepBasic_DateTimeRole), aRole);

  occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>> aItems;
  StepAP214_AutoDesignDateAndTimeItem                                   aItemsItem;
  int                                                                   nsub3;
  if (data->ReadSubList(num, 3, "items", ach, nsub3))
  {
    int nb3 = data->NbParams(nsub3);
    aItems  = new NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {
      bool stat3 = data->ReadEntity(nsub3, i3, "items", ach, aItemsItem);
      if (stat3)
        aItems->SetValue(i3, aItemsItem);
    }
  }

  ent->Init(aAssignedDateAndTime, aRole, aItems);
}

void RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment::WriteStep(
  StepData_StepWriter&                                                 SW,
  const occ::handle<StepAP214_AutoDesignNominalDateAndTimeAssignment>& ent) const
{

  SW.Send(ent->AssignedDateAndTime());

  SW.Send(ent->Role());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbItems(); i3++)
  {
    SW.Send(ent->ItemsValue(i3).Value());
  }
  SW.CloseSub();
}

void RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment::Share(
  const occ::handle<StepAP214_AutoDesignNominalDateAndTimeAssignment>& ent,
  Interface_EntityIterator&                                            iter) const
{

  iter.GetOneItem(ent->AssignedDateAndTime());

  iter.GetOneItem(ent->Role());

  int nbElem3 = ent->NbItems();
  for (int is3 = 1; is3 <= nbElem3; is3++)
  {
    iter.GetOneItem(ent->ItemsValue(is3).Value());
  }
}
