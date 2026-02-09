

#include <StepRepr_CompoundRepresentationItem.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_CompoundRepresentationItem, StepRepr_RepresentationItem)

StepRepr_CompoundRepresentationItem::StepRepr_CompoundRepresentationItem() = default;

void StepRepr_CompoundRepresentationItem::Init(
  const occ::handle<TCollection_HAsciiString>&                                      aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& item_element)
{
  StepRepr_RepresentationItem::Init(aName);
  theItemElement = item_element;
}

occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>
  StepRepr_CompoundRepresentationItem::ItemElement() const
{
  return theItemElement;
}

int StepRepr_CompoundRepresentationItem::NbItemElement() const
{
  return (theItemElement.IsNull() ? 0 : theItemElement->Length());
}

void StepRepr_CompoundRepresentationItem::SetItemElement(
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& item_element)
{
  theItemElement = item_element;
}

occ::handle<StepRepr_RepresentationItem> StepRepr_CompoundRepresentationItem::ItemElementValue(
  const int num) const
{
  return theItemElement->Value(num);
}

void StepRepr_CompoundRepresentationItem::SetItemElementValue(
  const int                                       num,
  const occ::handle<StepRepr_RepresentationItem>& anelement)
{
  theItemElement->SetValue(num, anelement);
}
