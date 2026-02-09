

#include <StepRepr_GlobalUnitAssignedContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_GlobalUnitAssignedContext, StepRepr_RepresentationContext)

StepRepr_GlobalUnitAssignedContext::StepRepr_GlobalUnitAssignedContext() = default;

void StepRepr_GlobalUnitAssignedContext::Init(
  const occ::handle<TCollection_HAsciiString>&                              aContextIdentifier,
  const occ::handle<TCollection_HAsciiString>&                              aContextType,
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits)
{

  units = aUnits;

  StepRepr_RepresentationContext::Init(aContextIdentifier, aContextType);
}

void StepRepr_GlobalUnitAssignedContext::SetUnits(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits)
{
  units = aUnits;
}

occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>
  StepRepr_GlobalUnitAssignedContext::Units() const
{
  return units;
}

occ::handle<StepBasic_NamedUnit> StepRepr_GlobalUnitAssignedContext::UnitsValue(const int num) const
{
  return units->Value(num);
}

int StepRepr_GlobalUnitAssignedContext::NbUnits() const
{
  if (units.IsNull())
    return 0;
  return units->Length();
}
