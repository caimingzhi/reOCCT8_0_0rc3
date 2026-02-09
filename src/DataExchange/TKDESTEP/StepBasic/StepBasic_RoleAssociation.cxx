#include <StepBasic_ObjectRole.hpp>
#include <StepBasic_RoleAssociation.hpp>
#include <StepBasic_RoleSelect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_RoleAssociation, Standard_Transient)

StepBasic_RoleAssociation::StepBasic_RoleAssociation() = default;

void StepBasic_RoleAssociation::Init(const occ::handle<StepBasic_ObjectRole>& aRole,
                                     const StepBasic_RoleSelect&              aItemWithRole)
{

  theRole = aRole;

  theItemWithRole = aItemWithRole;
}

occ::handle<StepBasic_ObjectRole> StepBasic_RoleAssociation::Role() const
{
  return theRole;
}

void StepBasic_RoleAssociation::SetRole(const occ::handle<StepBasic_ObjectRole>& aRole)
{
  theRole = aRole;
}

StepBasic_RoleSelect StepBasic_RoleAssociation::ItemWithRole() const
{
  return theItemWithRole;
}

void StepBasic_RoleAssociation::SetItemWithRole(const StepBasic_RoleSelect& aItemWithRole)
{
  theItemWithRole = aItemWithRole;
}
