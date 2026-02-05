#pragma once

#include <Standard.hpp>

#include <StepAP203_ApprovedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ApprovalAssignment.hpp>
class StepBasic_Approval;

//! Representation of STEP entity CcDesignApproval
class StepAP203_CcDesignApproval : public StepBasic_ApprovalAssignment
{

public:
  //! Empty constructor
  Standard_EXPORT StepAP203_CcDesignApproval();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Approval>& aApprovalAssignment_AssignedApproval,
    const occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>>& aItems);

  //! Returns field Items
  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> Items() const;

  //! Set field Items
  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_CcDesignApproval, StepBasic_ApprovalAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> theItems;
};
