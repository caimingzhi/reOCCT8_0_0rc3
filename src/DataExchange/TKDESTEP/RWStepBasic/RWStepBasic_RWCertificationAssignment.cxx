#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWCertificationAssignment.hpp"
#include <StepBasic_Certification.hpp>
#include <StepBasic_CertificationAssignment.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWCertificationAssignment::RWStepBasic_RWCertificationAssignment() = default;

void RWStepBasic_RWCertificationAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepBasic_CertificationAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "certification_assignment"))
    return;

  occ::handle<StepBasic_Certification> aAssignedCertification;
  data->ReadEntity(num,
                   1,
                   "assigned_certification",
                   ach,
                   STANDARD_TYPE(StepBasic_Certification),
                   aAssignedCertification);

  ent->Init(aAssignedCertification);
}

void RWStepBasic_RWCertificationAssignment::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepBasic_CertificationAssignment>& ent) const
{

  SW.Send(ent->AssignedCertification());
}

void RWStepBasic_RWCertificationAssignment::Share(
  const occ::handle<StepBasic_CertificationAssignment>& ent,
  Interface_EntityIterator&                             iter) const
{

  iter.AddItem(ent->AssignedCertification());
}
