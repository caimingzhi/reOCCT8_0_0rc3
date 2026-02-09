

#include <StepBasic_OrganizationRole.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_OrganizationRole, Standard_Transient)

StepBasic_OrganizationRole::StepBasic_OrganizationRole() = default;

void StepBasic_OrganizationRole::Init(const occ::handle<TCollection_HAsciiString>& aName)
{

  name = aName;
}

void StepBasic_OrganizationRole::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_OrganizationRole::Name() const
{
  return name;
}
