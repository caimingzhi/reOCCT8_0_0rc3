

#include <StepBasic_ApprovalRole.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ApprovalRole, Standard_Transient)

StepBasic_ApprovalRole::StepBasic_ApprovalRole() = default;

void StepBasic_ApprovalRole::Init(const occ::handle<TCollection_HAsciiString>& aRole)
{

  role = aRole;
}

void StepBasic_ApprovalRole::SetRole(const occ::handle<TCollection_HAsciiString>& aRole)
{
  role = aRole;
}

occ::handle<TCollection_HAsciiString> StepBasic_ApprovalRole::Role() const
{
  return role;
}
