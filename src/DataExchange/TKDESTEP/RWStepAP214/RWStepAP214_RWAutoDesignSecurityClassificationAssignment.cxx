

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAutoDesignSecurityClassificationAssignment.hpp"
#include <StepAP214_AutoDesignSecurityClassificationAssignment.hpp>
#include <StepBasic_Approval.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_SecurityClassification.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAutoDesignSecurityClassificationAssignment::
  RWStepAP214_RWAutoDesignSecurityClassificationAssignment() = default;

void RWStepAP214_RWAutoDesignSecurityClassificationAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&                              data,
  const int                                                                num,
  occ::handle<Interface_Check>&                                            ach,
  const occ::handle<StepAP214_AutoDesignSecurityClassificationAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "auto_design_security_classification_assignment"))
    return;

  occ::handle<StepBasic_SecurityClassification> aAssignedSecurityClassification;
  data->ReadEntity(num,
                   1,
                   "assigned_security_classification",
                   ach,
                   STANDARD_TYPE(StepBasic_SecurityClassification),
                   aAssignedSecurityClassification);

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Approval>>> aItems;
  occ::handle<StepBasic_Approval>                                   anent2;
  int                                                               nsub2;
  if (data->ReadSubList(num, 2, "items", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aItems  = new NCollection_HArray1<occ::handle<StepBasic_Approval>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {
      bool stat2 = data->ReadEntity(nsub2,
                                    i2,
                                    "auto_design_security_classified_item",
                                    ach,
                                    STANDARD_TYPE(StepBasic_Approval),
                                    anent2);
      if (stat2)
        aItems->SetValue(i2, anent2);
    }
  }

  ent->Init(aAssignedSecurityClassification, aItems);
}

void RWStepAP214_RWAutoDesignSecurityClassificationAssignment::WriteStep(
  StepData_StepWriter&                                                     SW,
  const occ::handle<StepAP214_AutoDesignSecurityClassificationAssignment>& ent) const
{

  SW.Send(ent->AssignedSecurityClassification());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbItems(); i2++)
  {
    SW.Send(ent->ItemsValue(i2));
  }
  SW.CloseSub();
}

void RWStepAP214_RWAutoDesignSecurityClassificationAssignment::Share(
  const occ::handle<StepAP214_AutoDesignSecurityClassificationAssignment>& ent,
  Interface_EntityIterator&                                                iter) const
{

  iter.GetOneItem(ent->AssignedSecurityClassification());

  int nbElem2 = ent->NbItems();
  for (int is2 = 1; is2 <= nbElem2; is2++)
  {
    iter.GetOneItem(ent->ItemsValue(is2));
  }
}
