#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWDocumentProductAssociation.hpp"
#include <StepBasic_Document.hpp>
#include <StepBasic_DocumentProductAssociation.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWDocumentProductAssociation::RWStepBasic_RWDocumentProductAssociation() = default;

void RWStepBasic_RWDocumentProductAssociation::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepBasic_DocumentProductAssociation>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "document_product_association"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  occ::handle<StepBasic_Document> aRelatingDocument;
  data->ReadEntity(num,
                   3,
                   "relating_document",
                   ach,
                   STANDARD_TYPE(StepBasic_Document),
                   aRelatingDocument);

  StepBasic_ProductOrFormationOrDefinition aRelatedProduct;
  data->ReadEntity(num, 4, "related_product", ach, aRelatedProduct);

  ent->Init(aName, hasDescription, aDescription, aRelatingDocument, aRelatedProduct);
}

void RWStepBasic_RWDocumentProductAssociation::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepBasic_DocumentProductAssociation>& ent) const
{

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->RelatingDocument());

  SW.Send(ent->RelatedProduct().Value());
}

void RWStepBasic_RWDocumentProductAssociation::Share(
  const occ::handle<StepBasic_DocumentProductAssociation>& ent,
  Interface_EntityIterator&                                iter) const
{

  iter.AddItem(ent->RelatingDocument());

  iter.AddItem(ent->RelatedProduct().Value());
}
