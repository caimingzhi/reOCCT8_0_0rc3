#pragma once

#include <Standard.hpp>

#include <StepAP203_SpecifiedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_DocumentReference.hpp>
class StepBasic_Document;
class TCollection_HAsciiString;

class StepAP203_CcDesignSpecificationReference : public StepBasic_DocumentReference
{

public:
  Standard_EXPORT StepAP203_CcDesignSpecificationReference();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Document>&       aDocumentReference_AssignedDocument,
    const occ::handle<TCollection_HAsciiString>& aDocumentReference_Source,
    const occ::handle<NCollection_HArray1<StepAP203_SpecifiedItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_SpecifiedItem>> Items() const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_SpecifiedItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_CcDesignSpecificationReference, StepBasic_DocumentReference)

private:
  occ::handle<NCollection_HArray1<StepAP203_SpecifiedItem>> theItems;
};
