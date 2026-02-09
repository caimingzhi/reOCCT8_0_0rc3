

#include <StepBasic_ApprovalStatus.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ApprovalStatus, Standard_Transient)

StepBasic_ApprovalStatus::StepBasic_ApprovalStatus() = default;

void StepBasic_ApprovalStatus::Init(const occ::handle<TCollection_HAsciiString>& aName)
{

  name = aName;
}

void StepBasic_ApprovalStatus::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_ApprovalStatus::Name() const
{
  return name;
}
