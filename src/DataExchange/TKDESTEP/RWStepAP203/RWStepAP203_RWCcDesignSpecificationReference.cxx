#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP203_RWCcDesignSpecificationReference.hpp"
#include <StepAP203_CcDesignSpecificationReference.hpp>
#include <StepAP203_SpecifiedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Document.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP203_RWCcDesignSpecificationReference::RWStepAP203_RWCcDesignSpecificationReference() =
  default;

void RWStepAP203_RWCcDesignSpecificationReference::ReadStep(
  const occ::handle<StepData_StepReaderData>&                  data,
  const int                                                    num,
  occ::handle<Interface_Check>&                                ach,
  const occ::handle<StepAP203_CcDesignSpecificationReference>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "cc_design_specification_reference"))
    return;

  occ::handle<StepBasic_Document> aDocumentReference_AssignedDocument;
  data->ReadEntity(num,
                   1,
                   "document_reference.assigned_document",
                   ach,
                   STANDARD_TYPE(StepBasic_Document),
                   aDocumentReference_AssignedDocument);

  occ::handle<TCollection_HAsciiString> aDocumentReference_Source;
  data->ReadString(num, 2, "document_reference.source", ach, aDocumentReference_Source);

  occ::handle<NCollection_HArray1<StepAP203_SpecifiedItem>> aItems;
  int                                                       sub3 = 0;
  if (data->ReadSubList(num, 3, "items", ach, sub3))
  {
    int num2 = sub3;
    int nb0  = data->NbParams(num2);
    aItems   = new NCollection_HArray1<StepAP203_SpecifiedItem>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepAP203_SpecifiedItem anIt0;
      data->ReadEntity(num2, i0, "items", ach, anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  ent->Init(aDocumentReference_AssignedDocument, aDocumentReference_Source, aItems);
}

void RWStepAP203_RWCcDesignSpecificationReference::WriteStep(
  StepData_StepWriter&                                         SW,
  const occ::handle<StepAP203_CcDesignSpecificationReference>& ent) const
{

  SW.Send(ent->StepBasic_DocumentReference::AssignedDocument());

  SW.Send(ent->StepBasic_DocumentReference::Source());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->Items()->Length(); i2++)
  {
    StepAP203_SpecifiedItem Var0 = ent->Items()->Value(i2);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

void RWStepAP203_RWCcDesignSpecificationReference::Share(
  const occ::handle<StepAP203_CcDesignSpecificationReference>& ent,
  Interface_EntityIterator&                                    iter) const
{

  iter.AddItem(ent->StepBasic_DocumentReference::AssignedDocument());

  for (int i2 = 1; i2 <= ent->Items()->Length(); i2++)
  {
    StepAP203_SpecifiedItem Var0 = ent->Items()->Value(i2);
    iter.AddItem(Var0.Value());
  }
}
