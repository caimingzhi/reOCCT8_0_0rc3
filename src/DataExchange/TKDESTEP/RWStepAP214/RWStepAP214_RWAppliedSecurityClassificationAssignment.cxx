

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAppliedSecurityClassificationAssignment.hpp"
#include <StepAP214_AppliedSecurityClassificationAssignment.hpp>
#include <StepAP214_SecurityClassificationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_SecurityClassification.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAppliedSecurityClassificationAssignment::
  RWStepAP214_RWAppliedSecurityClassificationAssignment() = default;

void RWStepAP214_RWAppliedSecurityClassificationAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&                           data,
  const int                                                             num,
  occ::handle<Interface_Check>&                                         ach,
  const occ::handle<StepAP214_AppliedSecurityClassificationAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "applied_security_classification_assignment"))
    return;

  occ::handle<StepBasic_SecurityClassification> aAssignedSecurityClassification;
  data->ReadEntity(num,
                   1,
                   "assigned_security_classification",
                   ach,
                   STANDARD_TYPE(StepBasic_SecurityClassification),
                   aAssignedSecurityClassification);

  occ::handle<NCollection_HArray1<StepAP214_SecurityClassificationItem>> aItems;
  StepAP214_SecurityClassificationItem                                   anent2;
  int                                                                    nsub2;
  if (data->ReadSubList(num, 2, "items", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aItems  = new NCollection_HArray1<StepAP214_SecurityClassificationItem>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {
      bool stat2 = data->ReadEntity(nsub2, i2, "items", ach, anent2);
      if (stat2)
        aItems->SetValue(i2, anent2);
    }
  }

  ent->Init(aAssignedSecurityClassification, aItems);
}

void RWStepAP214_RWAppliedSecurityClassificationAssignment::WriteStep(
  StepData_StepWriter&                                                  SW,
  const occ::handle<StepAP214_AppliedSecurityClassificationAssignment>& ent) const
{

  SW.Send(ent->AssignedSecurityClassification());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbItems(); i2++)
  {
    SW.Send(ent->ItemsValue(i2).Value());
  }
  SW.CloseSub();
}

void RWStepAP214_RWAppliedSecurityClassificationAssignment::Share(
  const occ::handle<StepAP214_AppliedSecurityClassificationAssignment>& ent,
  Interface_EntityIterator&                                             iter) const
{

  iter.GetOneItem(ent->AssignedSecurityClassification());

  int nbElem2 = ent->NbItems();
  for (int is2 = 1; is2 <= nbElem2; is2++)
  {
    iter.GetOneItem(ent->ItemsValue(is2).Value());
  }
}
