

#include <StepRepr_GlobalUncertaintyAssignedContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_GlobalUncertaintyAssignedContext,
                           StepRepr_RepresentationContext)

StepRepr_GlobalUncertaintyAssignedContext::StepRepr_GlobalUncertaintyAssignedContext() = default;

void StepRepr_GlobalUncertaintyAssignedContext::Init(
  const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
  const occ::handle<TCollection_HAsciiString>& aContextType,
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>&
    aUncertainty)
{

  uncertainty = aUncertainty;

  StepRepr_RepresentationContext::Init(aContextIdentifier, aContextType);
}

void StepRepr_GlobalUncertaintyAssignedContext::SetUncertainty(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>&
    aUncertainty)
{
  uncertainty = aUncertainty;
}

occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>
  StepRepr_GlobalUncertaintyAssignedContext::Uncertainty() const
{
  return uncertainty;
}

occ::handle<StepBasic_UncertaintyMeasureWithUnit> StepRepr_GlobalUncertaintyAssignedContext::
  UncertaintyValue(const int num) const
{
  return uncertainty->Value(num);
}

int StepRepr_GlobalUncertaintyAssignedContext::NbUncertainty() const
{
  if (uncertainty.IsNull())
    return 0;
  return uncertainty->Length();
}
