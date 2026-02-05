#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWCertificationType.hpp"
#include <StepBasic_CertificationType.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWCertificationType::RWStepBasic_RWCertificationType() = default;

//=================================================================================================

void RWStepBasic_RWCertificationType::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepBasic_CertificationType>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "certification_type"))
    return;

  // Own fields of CertificationType

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 1, "description", ach, aDescription);

  // Initialize entity
  ent->Init(aDescription);
}

//=================================================================================================

void RWStepBasic_RWCertificationType::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepBasic_CertificationType>& ent) const
{

  // Own fields of CertificationType

  SW.Send(ent->Description());
}

//=================================================================================================

void RWStepBasic_RWCertificationType::Share(const occ::handle<StepBasic_CertificationType>&,
                                            Interface_EntityIterator&) const
{
  // Own fields of CertificationType
}
