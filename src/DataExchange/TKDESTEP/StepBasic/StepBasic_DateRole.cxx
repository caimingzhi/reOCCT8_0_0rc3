

#include <StepBasic_DateRole.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DateRole, Standard_Transient)

StepBasic_DateRole::StepBasic_DateRole() = default;

void StepBasic_DateRole::Init(const occ::handle<TCollection_HAsciiString>& aName)
{

  name = aName;
}

void StepBasic_DateRole::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_DateRole::Name() const
{
  return name;
}
