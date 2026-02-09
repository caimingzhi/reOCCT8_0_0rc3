#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_Approval;

class StepBasic_ApprovalRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ApprovalRelationship();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepBasic_Approval>&       aRelatingApproval,
                            const occ::handle<StepBasic_Approval>&       aRelatedApproval);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetRelatingApproval(
    const occ::handle<StepBasic_Approval>& aRelatingApproval);

  Standard_EXPORT occ::handle<StepBasic_Approval> RelatingApproval() const;

  Standard_EXPORT void SetRelatedApproval(const occ::handle<StepBasic_Approval>& aRelatedApproval);

  Standard_EXPORT occ::handle<StepBasic_Approval> RelatedApproval() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ApprovalRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> name;
  occ::handle<TCollection_HAsciiString> description;
  occ::handle<StepBasic_Approval>       relatingApproval;
  occ::handle<StepBasic_Approval>       relatedApproval;
};
