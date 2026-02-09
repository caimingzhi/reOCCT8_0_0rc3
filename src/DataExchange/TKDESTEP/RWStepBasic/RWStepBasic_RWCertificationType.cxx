#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWCertificationType.hpp"
#include <StepBasic_CertificationType.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWCertificationType::RWStepBasic_RWCertificationType() = default;

void RWStepBasic_RWCertificationType::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepBasic_CertificationType>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "certification_type"))
    return;

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 1, "description", ach, aDescription);

  ent->Init(aDescription);
}

void RWStepBasic_RWCertificationType::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepBasic_CertificationType>& ent) const
{

  SW.Send(ent->Description());
}

void RWStepBasic_RWCertificationType::Share(const occ::handle<StepBasic_CertificationType>&,
                                            Interface_EntityIterator&) const
{
}
