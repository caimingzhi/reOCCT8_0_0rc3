

#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalStatus.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_Approval, Standard_Transient)

StepBasic_Approval::StepBasic_Approval() = default;

void StepBasic_Approval::Init(const occ::handle<StepBasic_ApprovalStatus>& aStatus,
                              const occ::handle<TCollection_HAsciiString>& aLevel)
{

  status = aStatus;
  level  = aLevel;
}

void StepBasic_Approval::SetStatus(const occ::handle<StepBasic_ApprovalStatus>& aStatus)
{
  status = aStatus;
}

occ::handle<StepBasic_ApprovalStatus> StepBasic_Approval::Status() const
{
  return status;
}

void StepBasic_Approval::SetLevel(const occ::handle<TCollection_HAsciiString>& aLevel)
{
  level = aLevel;
}

occ::handle<TCollection_HAsciiString> StepBasic_Approval::Level() const
{
  return level;
}
