#pragma once


#include <Standard.hpp>

#include <StepAP214_ApprovalItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ApprovalAssignment.hpp>
#include <Standard_Integer.hpp>
class StepBasic_Approval;
class StepAP214_ApprovalItem;

class StepAP214_AppliedApprovalAssignment : public StepBasic_ApprovalAssignment
{

public:
  //! Returns a AppliedApprovalAssignment
  Standard_EXPORT StepAP214_AppliedApprovalAssignment();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Approval>& aAssignedApproval,
                            const occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>>& aItems);

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>> Items() const;

  Standard_EXPORT StepAP214_ApprovalItem ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AppliedApprovalAssignment, StepBasic_ApprovalAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>> items;
};

