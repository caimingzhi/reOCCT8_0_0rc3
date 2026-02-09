

#include <StepBasic_DateTimeRole.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DateTimeRole, Standard_Transient)

StepBasic_DateTimeRole::StepBasic_DateTimeRole() = default;

void StepBasic_DateTimeRole::Init(const occ::handle<TCollection_HAsciiString>& aName)
{

  name = aName;
}

void StepBasic_DateTimeRole::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_DateTimeRole::Name() const
{
  return name;
}
