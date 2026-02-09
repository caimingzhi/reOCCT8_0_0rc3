

#include <StepAP214_AutoDesignDocumentReference.hpp>
#include <StepAP214_AutoDesignReferencingItem.hpp>
#include <StepBasic_Document.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignDocumentReference, StepBasic_DocumentReference)

StepAP214_AutoDesignDocumentReference::StepAP214_AutoDesignDocumentReference() = default;

void StepAP214_AutoDesignDocumentReference::Init(
  const occ::handle<StepBasic_Document>&                                       aAssignedDocument,
  const occ::handle<TCollection_HAsciiString>&                                 aSource,
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignReferencingItem>>& aItems)
{
  Init0(aAssignedDocument, aSource);
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignReferencingItem>>
  StepAP214_AutoDesignDocumentReference::Items() const
{
  return items;
}

void StepAP214_AutoDesignDocumentReference::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignReferencingItem>>& aItems)
{
  items = aItems;
}

StepAP214_AutoDesignReferencingItem StepAP214_AutoDesignDocumentReference::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignDocumentReference::NbItems() const
{
  return (items.IsNull() ? 0 : items->Length());
}
