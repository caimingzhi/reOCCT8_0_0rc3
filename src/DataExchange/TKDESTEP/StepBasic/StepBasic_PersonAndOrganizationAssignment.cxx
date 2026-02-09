

#include <Standard_Type.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepBasic_PersonAndOrganizationAssignment.hpp>
#include <StepBasic_PersonAndOrganizationRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_PersonAndOrganizationAssignment, Standard_Transient)

void StepBasic_PersonAndOrganizationAssignment::Init(
  const occ::handle<StepBasic_PersonAndOrganization>&     aAssignedPersonAndOrganization,
  const occ::handle<StepBasic_PersonAndOrganizationRole>& aRole)
{

  assignedPersonAndOrganization = aAssignedPersonAndOrganization;
  role                          = aRole;
}

void StepBasic_PersonAndOrganizationAssignment::SetAssignedPersonAndOrganization(
  const occ::handle<StepBasic_PersonAndOrganization>& aAssignedPersonAndOrganization)
{
  assignedPersonAndOrganization = aAssignedPersonAndOrganization;
}

occ::handle<StepBasic_PersonAndOrganization> StepBasic_PersonAndOrganizationAssignment::
  AssignedPersonAndOrganization() const
{
  return assignedPersonAndOrganization;
}

void StepBasic_PersonAndOrganizationAssignment::SetRole(
  const occ::handle<StepBasic_PersonAndOrganizationRole>& aRole)
{
  role = aRole;
}

occ::handle<StepBasic_PersonAndOrganizationRole> StepBasic_PersonAndOrganizationAssignment::Role()
  const
{
  return role;
}
