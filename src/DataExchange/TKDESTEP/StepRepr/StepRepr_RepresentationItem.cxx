

#include <StepRepr_RepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_RepresentationItem, Standard_Transient)

StepRepr_RepresentationItem::StepRepr_RepresentationItem() = default;

void StepRepr_RepresentationItem::Init(const occ::handle<TCollection_HAsciiString>& aName)
{

  name = aName;
}

void StepRepr_RepresentationItem::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_RepresentationItem::Name() const
{
  return name;
}
