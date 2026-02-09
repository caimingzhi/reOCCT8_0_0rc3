

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWDocumentUsageConstraint.hpp"
#include <StepBasic_Document.hpp>
#include <StepBasic_DocumentUsageConstraint.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepBasic_RWDocumentUsageConstraint::RWStepBasic_RWDocumentUsageConstraint() = default;

void RWStepBasic_RWDocumentUsageConstraint::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepBasic_DocumentUsageConstraint>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "document_usage_constraint"))
    return;

  occ::handle<StepBasic_Document> aSource;

  data->ReadEntity(num, 1, "source", ach, STANDARD_TYPE(StepBasic_Document), aSource);

  occ::handle<TCollection_HAsciiString> aLabel;

  data->ReadString(num, 2, "subject_element", ach, aLabel);

  occ::handle<TCollection_HAsciiString> aDescription;

  data->ReadString(num, 3, "subject_element_value", ach, aDescription);

  ent->Init(aSource, aLabel, aDescription);
}

void RWStepBasic_RWDocumentUsageConstraint::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepBasic_DocumentUsageConstraint>& ent) const
{

  SW.Send(ent->Source());

  SW.Send(ent->SubjectElement());

  SW.Send(ent->SubjectElementValue());
}

void RWStepBasic_RWDocumentUsageConstraint::Share(
  const occ::handle<StepBasic_DocumentUsageConstraint>& ent,
  Interface_EntityIterator&                             iter) const
{
  iter.AddItem(ent->Source());
}
