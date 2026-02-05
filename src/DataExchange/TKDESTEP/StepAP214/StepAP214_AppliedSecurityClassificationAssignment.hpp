#pragma once

#include <Standard.hpp>

#include <StepAP214_SecurityClassificationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_SecurityClassificationAssignment.hpp>
#include <Standard_Integer.hpp>
class StepBasic_SecurityClassification;
class StepAP214_SecurityClassificationItem;

class StepAP214_AppliedSecurityClassificationAssignment
    : public StepBasic_SecurityClassificationAssignment
{

public:
  //! Returns a AppliedSecurityClassificationAssignment
  Standard_EXPORT StepAP214_AppliedSecurityClassificationAssignment();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_SecurityClassification>& aAssignedSecurityClassification,
    const occ::handle<NCollection_HArray1<StepAP214_SecurityClassificationItem>>& aItems);

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_SecurityClassificationItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_SecurityClassificationItem>> Items()
    const;

  Standard_EXPORT const StepAP214_SecurityClassificationItem& ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AppliedSecurityClassificationAssignment,
                          StepBasic_SecurityClassificationAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_SecurityClassificationItem>> items;
};
