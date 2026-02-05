#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Approval;

class StepBasic_ApprovalAssignment : public Standard_Transient
{

public:
  Standard_EXPORT void Init(const occ::handle<StepBasic_Approval>& aAssignedApproval);

  Standard_EXPORT void SetAssignedApproval(
    const occ::handle<StepBasic_Approval>& aAssignedApproval);

  Standard_EXPORT occ::handle<StepBasic_Approval> AssignedApproval() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ApprovalAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Approval> assignedApproval;
};
