#include <StepBasic_MeasureValueMember.hpp>
#include <StepRepr_ValueRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ValueRepresentationItem, StepRepr_RepresentationItem)

StepRepr_ValueRepresentationItem::StepRepr_ValueRepresentationItem() = default;

void StepRepr_ValueRepresentationItem::Init(
  const occ::handle<TCollection_HAsciiString>&     theName,
  const occ::handle<StepBasic_MeasureValueMember>& theValueComponentMember)
{
  valueComponentMember = theValueComponentMember;
  StepRepr_RepresentationItem::Init(theName);
}
