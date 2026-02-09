

#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalDateTime.hpp>
#include <StepBasic_DateTimeSelect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ApprovalDateTime, Standard_Transient)

StepBasic_ApprovalDateTime::StepBasic_ApprovalDateTime() = default;

void StepBasic_ApprovalDateTime::Init(const StepBasic_DateTimeSelect&        aDateTime,
                                      const occ::handle<StepBasic_Approval>& aDatedApproval)
{
  theDateTime      = aDateTime;
  theDatedApproval = aDatedApproval;
}

void StepBasic_ApprovalDateTime::SetDateTime(const StepBasic_DateTimeSelect& aDateTime)
{
  theDateTime = aDateTime;
}

StepBasic_DateTimeSelect StepBasic_ApprovalDateTime::DateTime() const
{
  return theDateTime;
}

void StepBasic_ApprovalDateTime::SetDatedApproval(
  const occ::handle<StepBasic_Approval>& aDatedApproval)
{
  theDatedApproval = aDatedApproval;
}

occ::handle<StepBasic_Approval> StepBasic_ApprovalDateTime::DatedApproval() const
{
  return theDatedApproval;
}
