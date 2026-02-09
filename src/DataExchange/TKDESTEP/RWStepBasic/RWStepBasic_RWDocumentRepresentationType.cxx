#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWDocumentRepresentationType.hpp"
#include <StepBasic_Document.hpp>
#include <StepBasic_DocumentRepresentationType.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWDocumentRepresentationType::RWStepBasic_RWDocumentRepresentationType() = default;

void RWStepBasic_RWDocumentRepresentationType::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepBasic_DocumentRepresentationType>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "document_representation_type"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepBasic_Document> aRepresentedDocument;
  data->ReadEntity(num,
                   2,
                   "represented_document",
                   ach,
                   STANDARD_TYPE(StepBasic_Document),
                   aRepresentedDocument);

  ent->Init(aName, aRepresentedDocument);
}

void RWStepBasic_RWDocumentRepresentationType::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepBasic_DocumentRepresentationType>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->RepresentedDocument());
}

void RWStepBasic_RWDocumentRepresentationType::Share(
  const occ::handle<StepBasic_DocumentRepresentationType>& ent,
  Interface_EntityIterator&                                iter) const
{

  iter.AddItem(ent->RepresentedDocument());
}
