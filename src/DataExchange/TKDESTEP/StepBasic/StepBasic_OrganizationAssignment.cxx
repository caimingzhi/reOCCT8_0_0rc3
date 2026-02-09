

#include <Standard_Type.hpp>
#include <StepBasic_Organization.hpp>
#include <StepBasic_OrganizationAssignment.hpp>
#include <StepBasic_OrganizationRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_OrganizationAssignment, Standard_Transient)

void StepBasic_OrganizationAssignment::Init(
  const occ::handle<StepBasic_Organization>&     aAssignedOrganization,
  const occ::handle<StepBasic_OrganizationRole>& aRole)
{

  assignedOrganization = aAssignedOrganization;
  role                 = aRole;
}

void StepBasic_OrganizationAssignment::SetAssignedOrganization(
  const occ::handle<StepBasic_Organization>& aAssignedOrganization)
{
  assignedOrganization = aAssignedOrganization;
}

occ::handle<StepBasic_Organization> StepBasic_OrganizationAssignment::AssignedOrganization() const
{
  return assignedOrganization;
}

void StepBasic_OrganizationAssignment::SetRole(const occ::handle<StepBasic_OrganizationRole>& aRole)
{
  role = aRole;
}

occ::handle<StepBasic_OrganizationRole> StepBasic_OrganizationAssignment::Role() const
{
  return role;
}
