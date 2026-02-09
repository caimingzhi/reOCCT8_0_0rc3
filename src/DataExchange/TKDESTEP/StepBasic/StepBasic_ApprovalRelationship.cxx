

#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ApprovalRelationship, Standard_Transient)

StepBasic_ApprovalRelationship::StepBasic_ApprovalRelationship() = default;

void StepBasic_ApprovalRelationship::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                          const occ::handle<TCollection_HAsciiString>& aDescription,
                                          const occ::handle<StepBasic_Approval>& aRelatingApproval,
                                          const occ::handle<StepBasic_Approval>& aRelatedApproval)
{

  name             = aName;
  description      = aDescription;
  relatingApproval = aRelatingApproval;
  relatedApproval  = aRelatedApproval;
}

void StepBasic_ApprovalRelationship::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_ApprovalRelationship::Name() const
{
  return name;
}

void StepBasic_ApprovalRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepBasic_ApprovalRelationship::Description() const
{
  return description;
}

void StepBasic_ApprovalRelationship::SetRelatingApproval(
  const occ::handle<StepBasic_Approval>& aRelatingApproval)
{
  relatingApproval = aRelatingApproval;
}

occ::handle<StepBasic_Approval> StepBasic_ApprovalRelationship::RelatingApproval() const
{
  return relatingApproval;
}

void StepBasic_ApprovalRelationship::SetRelatedApproval(
  const occ::handle<StepBasic_Approval>& aRelatedApproval)
{
  relatedApproval = aRelatedApproval;
}

occ::handle<StepBasic_Approval> StepBasic_ApprovalRelationship::RelatedApproval() const
{
  return relatedApproval;
}
