#include <StepAP203_CcDesignSpecificationReference.hpp>
#include <StepBasic_Document.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_CcDesignSpecificationReference, StepBasic_DocumentReference)

//=================================================================================================

StepAP203_CcDesignSpecificationReference::StepAP203_CcDesignSpecificationReference() = default;

//=================================================================================================

void StepAP203_CcDesignSpecificationReference::Init(
  const occ::handle<StepBasic_Document>&       aDocumentReference_AssignedDocument,
  const occ::handle<TCollection_HAsciiString>& aDocumentReference_Source,
  const occ::handle<NCollection_HArray1<StepAP203_SpecifiedItem>>& aItems)
{
  StepBasic_DocumentReference::Init0(aDocumentReference_AssignedDocument,
                                     aDocumentReference_Source);

  theItems = aItems;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepAP203_SpecifiedItem>> StepAP203_CcDesignSpecificationReference::
  Items() const
{
  return theItems;
}

//=================================================================================================

void StepAP203_CcDesignSpecificationReference::SetItems(
  const occ::handle<NCollection_HArray1<StepAP203_SpecifiedItem>>& aItems)
{
  theItems = aItems;
}
