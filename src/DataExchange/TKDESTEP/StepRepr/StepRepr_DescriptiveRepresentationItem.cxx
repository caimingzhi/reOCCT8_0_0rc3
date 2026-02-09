

#include <StepRepr_DescriptiveRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_DescriptiveRepresentationItem, StepRepr_RepresentationItem)

StepRepr_DescriptiveRepresentationItem::StepRepr_DescriptiveRepresentationItem() = default;

void StepRepr_DescriptiveRepresentationItem::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<TCollection_HAsciiString>& aDescription)
{

  description = aDescription;

  StepRepr_RepresentationItem::Init(aName);
}

void StepRepr_DescriptiveRepresentationItem::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepRepr_DescriptiveRepresentationItem::Description() const
{
  return description;
}
