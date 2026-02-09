

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWDocumentRelationship.hpp"
#include <StepBasic_Document.hpp>
#include <StepBasic_DocumentRelationship.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepBasic_RWDocumentRelationship::RWStepBasic_RWDocumentRelationship() = default;

void RWStepBasic_RWDocumentRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepBasic_DocumentRelationship>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "document_relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescr;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "description", ach, aDescr);
  }

  occ::handle<StepBasic_Document> aRelating;

  data->ReadEntity(num, 3, "relating_document", ach, STANDARD_TYPE(StepBasic_Document), aRelating);

  occ::handle<StepBasic_Document> aRelated;

  data->ReadEntity(num, 4, "related_document", ach, STANDARD_TYPE(StepBasic_Document), aRelated);

  ent->Init(aName, aDescr, aRelating, aRelated);
}

void RWStepBasic_RWDocumentRelationship::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepBasic_DocumentRelationship>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->RelatingDocument());
  SW.Send(ent->RelatedDocument());
}

void RWStepBasic_RWDocumentRelationship::Share(
  const occ::handle<StepBasic_DocumentRelationship>& ent,
  Interface_EntityIterator&                          iter) const
{

  iter.AddItem(ent->RelatingDocument());
  iter.AddItem(ent->RelatedDocument());
}
