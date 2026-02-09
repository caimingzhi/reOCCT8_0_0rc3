

#include <Standard_Type.hpp>
#include <StepAP214_AutoDesignSecurityClassificationAssignment.hpp>
#include <StepBasic_Approval.hpp>
#include <StepBasic_SecurityClassification.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignSecurityClassificationAssignment,
                           StepBasic_SecurityClassificationAssignment)

StepAP214_AutoDesignSecurityClassificationAssignment::
  StepAP214_AutoDesignSecurityClassificationAssignment() = default;

void StepAP214_AutoDesignSecurityClassificationAssignment::Init(
  const occ::handle<StepBasic_SecurityClassification>& aAssignedSecurityClassification,
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Approval>>>& aItems)
{

  items = aItems;

  StepBasic_SecurityClassificationAssignment::Init(aAssignedSecurityClassification);
}

void StepAP214_AutoDesignSecurityClassificationAssignment::SetItems(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Approval>>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<occ::handle<StepBasic_Approval>>>
  StepAP214_AutoDesignSecurityClassificationAssignment::Items() const
{
  return items;
}

occ::handle<StepBasic_Approval> StepAP214_AutoDesignSecurityClassificationAssignment::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignSecurityClassificationAssignment::NbItems() const
{
  if (items.IsNull())
    return 0;
  return items->Length();
}
