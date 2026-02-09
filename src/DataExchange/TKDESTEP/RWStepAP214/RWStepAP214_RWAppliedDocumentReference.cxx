

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAppliedDocumentReference.hpp"
#include <StepAP214_AppliedDocumentReference.hpp>
#include <StepAP214_DocumentReferenceItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Document.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepAP214_RWAppliedDocumentReference::RWStepAP214_RWAppliedDocumentReference() = default;

void RWStepAP214_RWAppliedDocumentReference::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepAP214_AppliedDocumentReference>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "applied_document_reference"))
    return;

  occ::handle<StepBasic_Document> adoc;
  data->ReadEntity(num, 1, "assigned_document", ach, STANDARD_TYPE(StepBasic_Document), adoc);

  occ::handle<TCollection_HAsciiString> asource;
  data->ReadString(num, 2, "source", ach, asource);

  occ::handle<NCollection_HArray1<StepAP214_DocumentReferenceItem>> aItems;
  StepAP214_DocumentReferenceItem                                   anItem;
  int                                                               nsub3;
  if (data->ReadSubList(num, 3, "items", ach, nsub3))
  {
    int nb3 = data->NbParams(nsub3);
    aItems  = new NCollection_HArray1<StepAP214_DocumentReferenceItem>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {
      bool stat3 = data->ReadEntity(nsub3, i3, "item", ach, anItem);
      if (stat3)
        aItems->SetValue(i3, anItem);
    }
  }

  ent->Init(adoc, asource, aItems);
}

void RWStepAP214_RWAppliedDocumentReference::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepAP214_AppliedDocumentReference>& ent) const
{

  SW.Send(ent->AssignedDocument());

  SW.Send(ent->Source());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbItems(); i3++)
  {
    SW.Send(ent->ItemsValue(i3).Value());
  }
  SW.CloseSub();
}

void RWStepAP214_RWAppliedDocumentReference::Share(
  const occ::handle<StepAP214_AppliedDocumentReference>& ent,
  Interface_EntityIterator&                              iter) const
{
  iter.AddItem(ent->AssignedDocument());
  for (int i3 = 1; i3 <= ent->NbItems(); i3++)
    iter.AddItem(ent->ItemsValue(i3).Value());
}
