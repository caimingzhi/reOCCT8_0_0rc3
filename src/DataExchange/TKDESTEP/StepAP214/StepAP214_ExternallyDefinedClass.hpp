#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepAP214_Class.hpp>
#include <Standard_Boolean.hpp>
class StepBasic_ExternallyDefinedItem;
class TCollection_HAsciiString;
class StepBasic_SourceItem;
class StepBasic_ExternalSource;

class StepAP214_ExternallyDefinedClass : public StepAP214_Class
{

public:
  Standard_EXPORT StepAP214_ExternallyDefinedClass();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aGroup_Name,
    const bool                                   hasGroup_Description,
    const occ::handle<TCollection_HAsciiString>& aGroup_Description,
    const StepBasic_SourceItem&                  aExternallyDefinedItem_ItemId,
    const occ::handle<StepBasic_ExternalSource>& aExternallyDefinedItem_Source);

  Standard_EXPORT occ::handle<StepBasic_ExternallyDefinedItem> ExternallyDefinedItem() const;

  Standard_EXPORT void SetExternallyDefinedItem(
    const occ::handle<StepBasic_ExternallyDefinedItem>& ExternallyDefinedItem);

  DEFINE_STANDARD_RTTIEXT(StepAP214_ExternallyDefinedClass, StepAP214_Class)

private:
  occ::handle<StepBasic_ExternallyDefinedItem> theExternallyDefinedItem;
};
