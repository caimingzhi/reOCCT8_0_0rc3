#pragma once

#include <Standard.hpp>

#include <StepAP214_DocumentReferenceItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_DocumentReference.hpp>
#include <Standard_Integer.hpp>
class StepBasic_Document;
class TCollection_HAsciiString;
class StepAP214_DocumentReferenceItem;

class StepAP214_AppliedDocumentReference : public StepBasic_DocumentReference
{

public:
  Standard_EXPORT StepAP214_AppliedDocumentReference();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Document>&                                   aAssignedDocument,
    const occ::handle<TCollection_HAsciiString>&                             aSource,
    const occ::handle<NCollection_HArray1<StepAP214_DocumentReferenceItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_DocumentReferenceItem>> Items() const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_DocumentReferenceItem>>& aItems);

  Standard_EXPORT StepAP214_DocumentReferenceItem ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AppliedDocumentReference, StepBasic_DocumentReference)

private:
  occ::handle<NCollection_HArray1<StepAP214_DocumentReferenceItem>> items;
};
