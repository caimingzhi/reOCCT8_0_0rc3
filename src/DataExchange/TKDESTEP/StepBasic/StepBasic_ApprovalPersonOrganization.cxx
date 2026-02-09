

#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalPersonOrganization.hpp>
#include <StepBasic_ApprovalRole.hpp>
#include <StepBasic_PersonOrganizationSelect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ApprovalPersonOrganization, Standard_Transient)

StepBasic_ApprovalPersonOrganization::StepBasic_ApprovalPersonOrganization() = default;

void StepBasic_ApprovalPersonOrganization::Init(
  const StepBasic_PersonOrganizationSelect&  aPersonOrganization,
  const occ::handle<StepBasic_Approval>&     aAuthorizedApproval,
  const occ::handle<StepBasic_ApprovalRole>& aRole)
{

  personOrganization = aPersonOrganization;
  authorizedApproval = aAuthorizedApproval;
  role               = aRole;
}

void StepBasic_ApprovalPersonOrganization::SetPersonOrganization(
  const StepBasic_PersonOrganizationSelect& aPersonOrganization)
{
  personOrganization = aPersonOrganization;
}

StepBasic_PersonOrganizationSelect StepBasic_ApprovalPersonOrganization::PersonOrganization() const
{
  return personOrganization;
}

void StepBasic_ApprovalPersonOrganization::SetAuthorizedApproval(
  const occ::handle<StepBasic_Approval>& aAuthorizedApproval)
{
  authorizedApproval = aAuthorizedApproval;
}

occ::handle<StepBasic_Approval> StepBasic_ApprovalPersonOrganization::AuthorizedApproval() const
{
  return authorizedApproval;
}

void StepBasic_ApprovalPersonOrganization::SetRole(const occ::handle<StepBasic_ApprovalRole>& aRole)
{
  role = aRole;
}

occ::handle<StepBasic_ApprovalRole> StepBasic_ApprovalPersonOrganization::Role() const
{
  return role;
}
