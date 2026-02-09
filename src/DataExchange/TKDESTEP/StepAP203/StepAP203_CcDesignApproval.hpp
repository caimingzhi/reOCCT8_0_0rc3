#pragma once

#include <Standard.hpp>

#include <StepAP203_ApprovedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ApprovalAssignment.hpp>
class StepBasic_Approval;

class StepAP203_CcDesignApproval : public StepBasic_ApprovalAssignment
{

public:
  Standard_EXPORT StepAP203_CcDesignApproval();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Approval>& aApprovalAssignment_AssignedApproval,
    const occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> Items() const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_CcDesignApproval, StepBasic_ApprovalAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> theItems;
};
