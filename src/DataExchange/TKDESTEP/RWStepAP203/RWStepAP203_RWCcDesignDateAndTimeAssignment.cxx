#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP203_RWCcDesignDateAndTimeAssignment.hpp"
#include <StepAP203_CcDesignDateAndTimeAssignment.hpp>
#include <StepAP203_DateTimeItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_DateTimeRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepAP203_RWCcDesignDateAndTimeAssignment::RWStepAP203_RWCcDesignDateAndTimeAssignment() =
  default;

//=================================================================================================

void RWStepAP203_RWCcDesignDateAndTimeAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepAP203_CcDesignDateAndTimeAssignment>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "cc_design_date_and_time_assignment"))
    return;

  // Inherited fields of DateAndTimeAssignment

  occ::handle<StepBasic_DateAndTime> aDateAndTimeAssignment_AssignedDateAndTime;
  data->ReadEntity(num,
                   1,
                   "date_and_time_assignment.assigned_date_and_time",
                   ach,
                   STANDARD_TYPE(StepBasic_DateAndTime),
                   aDateAndTimeAssignment_AssignedDateAndTime);

  occ::handle<StepBasic_DateTimeRole> aDateAndTimeAssignment_Role;
  data->ReadEntity(num,
                   2,
                   "date_and_time_assignment.role",
                   ach,
                   STANDARD_TYPE(StepBasic_DateTimeRole),
                   aDateAndTimeAssignment_Role);

  // Own fields of CcDesignDateAndTimeAssignment

  occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>> aItems;
  int                                                      sub3 = 0;
  if (data->ReadSubList(num, 3, "items", ach, sub3))
  {
    int num2 = sub3;
    int nb0  = data->NbParams(num2);
    aItems   = new NCollection_HArray1<StepAP203_DateTimeItem>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepAP203_DateTimeItem anIt0;
      data->ReadEntity(num2, i0, "items", ach, anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aDateAndTimeAssignment_AssignedDateAndTime, aDateAndTimeAssignment_Role, aItems);
}

//=================================================================================================

void RWStepAP203_RWCcDesignDateAndTimeAssignment::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepAP203_CcDesignDateAndTimeAssignment>& ent) const
{

  // Inherited fields of DateAndTimeAssignment

  SW.Send(ent->StepBasic_DateAndTimeAssignment::AssignedDateAndTime());

  SW.Send(ent->StepBasic_DateAndTimeAssignment::Role());

  // Own fields of CcDesignDateAndTimeAssignment

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->Items()->Length(); i2++)
  {
    StepAP203_DateTimeItem Var0 = ent->Items()->Value(i2);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepAP203_RWCcDesignDateAndTimeAssignment::Share(
  const occ::handle<StepAP203_CcDesignDateAndTimeAssignment>& ent,
  Interface_EntityIterator&                                   iter) const
{

  // Inherited fields of DateAndTimeAssignment

  iter.AddItem(ent->StepBasic_DateAndTimeAssignment::AssignedDateAndTime());

  iter.AddItem(ent->StepBasic_DateAndTimeAssignment::Role());

  // Own fields of CcDesignDateAndTimeAssignment

  for (int i3 = 1; i3 <= ent->Items()->Length(); i3++)
  {
    StepAP203_DateTimeItem Var0 = ent->Items()->Value(i3);
    iter.AddItem(Var0.Value());
  }
}
