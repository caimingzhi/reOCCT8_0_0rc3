#include <StepRepr_IntegerRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_IntegerRepresentationItem, StepRepr_RepresentationItem)

StepRepr_IntegerRepresentationItem::StepRepr_IntegerRepresentationItem() = default;

void StepRepr_IntegerRepresentationItem::Init(const occ::handle<TCollection_HAsciiString>& theName,
                                              const int                                    theValue)
{
  value = theValue;
  StepRepr_RepresentationItem::Init(theName);
}
