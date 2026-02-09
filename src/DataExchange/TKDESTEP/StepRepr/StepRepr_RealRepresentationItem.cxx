

#include <StepRepr_RealRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_RealRepresentationItem, StepRepr_RepresentationItem)

StepRepr_RealRepresentationItem::StepRepr_RealRepresentationItem() = default;

void StepRepr_RealRepresentationItem::Init(const occ::handle<TCollection_HAsciiString>& theName,
                                           const double                                 theValue)
{
  value = theValue;
  StepRepr_RepresentationItem::Init(theName);
}
