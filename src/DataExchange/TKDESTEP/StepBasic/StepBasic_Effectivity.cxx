

#include <StepBasic_Effectivity.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_Effectivity, Standard_Transient)

StepBasic_Effectivity::StepBasic_Effectivity() = default;

void StepBasic_Effectivity::Init(const occ::handle<TCollection_HAsciiString>& aid)
{
  theid = aid;
}

occ::handle<TCollection_HAsciiString> StepBasic_Effectivity::Id() const
{
  return theid;
}

void StepBasic_Effectivity::SetId(const occ::handle<TCollection_HAsciiString>& aid)
{
  theid = aid;
}
