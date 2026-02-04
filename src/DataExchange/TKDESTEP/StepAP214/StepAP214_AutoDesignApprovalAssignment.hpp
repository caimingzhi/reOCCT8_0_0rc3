#pragma once


#include <Standard.hpp>

#include <StepAP214_AutoDesignGeneralOrgItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ApprovalAssignment.hpp>
#include <Standard_Integer.hpp>
class StepBasic_Approval;
class StepAP214_AutoDesignGeneralOrgItem;

class StepAP214_AutoDesignApprovalAssignment : public StepBasic_ApprovalAssignment
{

public:
  //! Returns a AutoDesignApprovalAssignment
  Standard_EXPORT StepAP214_AutoDesignApprovalAssignment();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Approval>&                                      aAssignedApproval,
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>& aItems);

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>> Items()
    const;

  Standard_EXPORT StepAP214_AutoDesignGeneralOrgItem ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AutoDesignApprovalAssignment, StepBasic_ApprovalAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>> items;
};

