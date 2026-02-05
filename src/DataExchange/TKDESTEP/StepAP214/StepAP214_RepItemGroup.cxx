#include <StepAP214_RepItemGroup.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_RepItemGroup, StepBasic_Group)

//=================================================================================================

StepAP214_RepItemGroup::StepAP214_RepItemGroup() = default;

//=================================================================================================

void StepAP214_RepItemGroup::Init(
  const occ::handle<TCollection_HAsciiString>& aGroup_Name,
  const bool                                   hasGroup_Description,
  const occ::handle<TCollection_HAsciiString>& aGroup_Description,
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name)
{
  StepBasic_Group::Init(aGroup_Name, hasGroup_Description, aGroup_Description);
  theRepresentationItem->Init(aRepresentationItem_Name);
}

//=================================================================================================

occ::handle<StepRepr_RepresentationItem> StepAP214_RepItemGroup::RepresentationItem() const
{
  return theRepresentationItem;
}

//=================================================================================================

void StepAP214_RepItemGroup::SetRepresentationItem(
  const occ::handle<StepRepr_RepresentationItem>& aRepresentationItem)
{
  theRepresentationItem = aRepresentationItem;
}
