#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWCertification.hpp"
#include <StepBasic_Certification.hpp>
#include <StepBasic_CertificationType.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWCertification::RWStepBasic_RWCertification() = default;

//=================================================================================================

void RWStepBasic_RWCertification::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepBasic_Certification>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "certification"))
    return;

  // Own fields of Certification

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aPurpose;
  data->ReadString(num, 2, "purpose", ach, aPurpose);

  occ::handle<StepBasic_CertificationType> aKind;
  data->ReadEntity(num, 3, "kind", ach, STANDARD_TYPE(StepBasic_CertificationType), aKind);

  // Initialize entity
  ent->Init(aName, aPurpose, aKind);
}

//=================================================================================================

void RWStepBasic_RWCertification::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepBasic_Certification>& ent) const
{

  // Own fields of Certification

  SW.Send(ent->Name());

  SW.Send(ent->Purpose());

  SW.Send(ent->Kind());
}

//=================================================================================================

void RWStepBasic_RWCertification::Share(const occ::handle<StepBasic_Certification>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  // Own fields of Certification

  iter.AddItem(ent->Kind());
}
