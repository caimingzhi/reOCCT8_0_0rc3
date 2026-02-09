#include <StepAP214_ExternallyDefinedClass.hpp>
#include <StepBasic_ExternallyDefinedItem.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_SourceItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_ExternallyDefinedClass, StepAP214_Class)

StepAP214_ExternallyDefinedClass::StepAP214_ExternallyDefinedClass() = default;

void StepAP214_ExternallyDefinedClass::Init(
  const occ::handle<TCollection_HAsciiString>& aGroup_Name,
  const bool                                   hasGroup_Description,
  const occ::handle<TCollection_HAsciiString>& aGroup_Description,
  const StepBasic_SourceItem&                  aExternallyDefinedItem_ItemId,
  const occ::handle<StepBasic_ExternalSource>& aExternallyDefinedItem_Source)
{
  StepAP214_Class::Init(aGroup_Name, hasGroup_Description, aGroup_Description);
  theExternallyDefinedItem->Init(aExternallyDefinedItem_ItemId, aExternallyDefinedItem_Source);
}

occ::handle<StepBasic_ExternallyDefinedItem> StepAP214_ExternallyDefinedClass::
  ExternallyDefinedItem() const
{
  return theExternallyDefinedItem;
}

void StepAP214_ExternallyDefinedClass::SetExternallyDefinedItem(
  const occ::handle<StepBasic_ExternallyDefinedItem>& aExternallyDefinedItem)
{
  theExternallyDefinedItem = aExternallyDefinedItem;
}
