

#include <StepAP214_AppliedDocumentReference.hpp>
#include <StepAP214_DocumentReferenceItem.hpp>
#include <StepBasic_Document.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AppliedDocumentReference, StepBasic_DocumentReference)

StepAP214_AppliedDocumentReference::StepAP214_AppliedDocumentReference() = default;

void StepAP214_AppliedDocumentReference::Init(
  const occ::handle<StepBasic_Document>&                                   aAssignedDocument,
  const occ::handle<TCollection_HAsciiString>&                             aSource,
  const occ::handle<NCollection_HArray1<StepAP214_DocumentReferenceItem>>& aItems)
{
  Init0(aAssignedDocument, aSource);
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_DocumentReferenceItem>>
  StepAP214_AppliedDocumentReference::Items() const
{
  return items;
}

void StepAP214_AppliedDocumentReference::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_DocumentReferenceItem>>& aItems)
{
  items = aItems;
}

StepAP214_DocumentReferenceItem StepAP214_AppliedDocumentReference::ItemsValue(const int num) const
{
  return items->Value(num);
}

int StepAP214_AppliedDocumentReference::NbItems() const
{
  return (items.IsNull() ? 0 : items->Length());
}
