#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP203_RWCcDesignCertification.hpp"
#include <StepAP203_CcDesignCertification.hpp>
#include <StepAP203_CertifiedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Certification.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP203_RWCcDesignCertification::RWStepAP203_RWCcDesignCertification() = default;

void RWStepAP203_RWCcDesignCertification::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepAP203_CcDesignCertification>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "cc_design_certification"))
    return;

  occ::handle<StepBasic_Certification> aCertificationAssignment_AssignedCertification;
  data->ReadEntity(num,
                   1,
                   "certification_assignment.assigned_certification",
                   ach,
                   STANDARD_TYPE(StepBasic_Certification),
                   aCertificationAssignment_AssignedCertification);

  occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>> aItems;
  int                                                       sub2 = 0;
  if (data->ReadSubList(num, 2, "items", ach, sub2))
  {
    int num2 = sub2;
    int nb0  = data->NbParams(num2);
    aItems   = new NCollection_HArray1<StepAP203_CertifiedItem>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepAP203_CertifiedItem anIt0;
      data->ReadEntity(num2, i0, "items", ach, anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  ent->Init(aCertificationAssignment_AssignedCertification, aItems);
}

void RWStepAP203_RWCcDesignCertification::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepAP203_CcDesignCertification>& ent) const
{

  SW.Send(ent->StepBasic_CertificationAssignment::AssignedCertification());

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->Items()->Length(); i1++)
  {
    StepAP203_CertifiedItem Var0 = ent->Items()->Value(i1);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

void RWStepAP203_RWCcDesignCertification::Share(
  const occ::handle<StepAP203_CcDesignCertification>& ent,
  Interface_EntityIterator&                           iter) const
{

  iter.AddItem(ent->StepBasic_CertificationAssignment::AssignedCertification());

  for (int i2 = 1; i2 <= ent->Items()->Length(); i2++)
  {
    StepAP203_CertifiedItem Var0 = ent->Items()->Value(i2);
    iter.AddItem(Var0.Value());
  }
}
