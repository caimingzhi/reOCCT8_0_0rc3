

#include <StepRepr_BooleanRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_BooleanRepresentationItem, StepRepr_RepresentationItem)

StepRepr_BooleanRepresentationItem::StepRepr_BooleanRepresentationItem() = default;

void StepRepr_BooleanRepresentationItem::Init(const occ::handle<TCollection_HAsciiString>& theName,
                                              const bool                                   theValue)
{
  value = theValue;
  StepRepr_RepresentationItem::Init(theName);
}
