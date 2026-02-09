#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_GeneralProperty.hpp>
#include <Standard_Boolean.hpp>
class StepBasic_ExternallyDefinedItem;
class TCollection_HAsciiString;
class StepBasic_SourceItem;
class StepBasic_ExternalSource;

class StepAP214_ExternallyDefinedGeneralProperty : public StepBasic_GeneralProperty
{

public:
  Standard_EXPORT StepAP214_ExternallyDefinedGeneralProperty();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aGeneralProperty_Id,
    const occ::handle<TCollection_HAsciiString>& aGeneralProperty_Name,
    const bool                                   hasGeneralProperty_Description,
    const occ::handle<TCollection_HAsciiString>& aGeneralProperty_Description,
    const StepBasic_SourceItem&                  aExternallyDefinedItem_ItemId,
    const occ::handle<StepBasic_ExternalSource>& aExternallyDefinedItem_Source);

  Standard_EXPORT occ::handle<StepBasic_ExternallyDefinedItem> ExternallyDefinedItem() const;

  Standard_EXPORT void SetExternallyDefinedItem(
    const occ::handle<StepBasic_ExternallyDefinedItem>& ExternallyDefinedItem);

  DEFINE_STANDARD_RTTIEXT(StepAP214_ExternallyDefinedGeneralProperty, StepBasic_GeneralProperty)

private:
  occ::handle<StepBasic_ExternallyDefinedItem> theExternallyDefinedItem;
};
