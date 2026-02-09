#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_PersonOrganizationSelect.hpp>
#include <Standard_Transient.hpp>
class StepBasic_Approval;
class StepBasic_ApprovalRole;

class StepBasic_ApprovalPersonOrganization : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ApprovalPersonOrganization();

  Standard_EXPORT void Init(const StepBasic_PersonOrganizationSelect&  aPersonOrganization,
                            const occ::handle<StepBasic_Approval>&     aAuthorizedApproval,
                            const occ::handle<StepBasic_ApprovalRole>& aRole);

  Standard_EXPORT void SetPersonOrganization(
    const StepBasic_PersonOrganizationSelect& aPersonOrganization);

  Standard_EXPORT StepBasic_PersonOrganizationSelect PersonOrganization() const;

  Standard_EXPORT void SetAuthorizedApproval(
    const occ::handle<StepBasic_Approval>& aAuthorizedApproval);

  Standard_EXPORT occ::handle<StepBasic_Approval> AuthorizedApproval() const;

  Standard_EXPORT void SetRole(const occ::handle<StepBasic_ApprovalRole>& aRole);

  Standard_EXPORT occ::handle<StepBasic_ApprovalRole> Role() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ApprovalPersonOrganization, Standard_Transient)

private:
  StepBasic_PersonOrganizationSelect  personOrganization;
  occ::handle<StepBasic_Approval>     authorizedApproval;
  occ::handle<StepBasic_ApprovalRole> role;
};
