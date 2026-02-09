

#include <StepBasic_PersonAndOrganizationRole.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_PersonAndOrganizationRole, Standard_Transient)

StepBasic_PersonAndOrganizationRole::StepBasic_PersonAndOrganizationRole() = default;

void StepBasic_PersonAndOrganizationRole::Init(const occ::handle<TCollection_HAsciiString>& aName)
{

  name = aName;
}

void StepBasic_PersonAndOrganizationRole::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_PersonAndOrganizationRole::Name() const
{
  return name;
}
