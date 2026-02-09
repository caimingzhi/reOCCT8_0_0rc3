

#include <StepAP214_AutoDesignDateAndPersonAssignment.hpp>
#include <StepAP214_AutoDesignDateAndPersonItem.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepBasic_PersonAndOrganizationRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignDateAndPersonAssignment,
                           StepBasic_PersonAndOrganizationAssignment)

StepAP214_AutoDesignDateAndPersonAssignment::StepAP214_AutoDesignDateAndPersonAssignment() =
  default;

void StepAP214_AutoDesignDateAndPersonAssignment::Init(
  const occ::handle<StepBasic_PersonAndOrganization>&     aAssignedPersonAndOrganization,
  const occ::handle<StepBasic_PersonAndOrganizationRole>& aRole,
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndPersonItem>>& aItems)
{

  items = aItems;

  StepBasic_PersonAndOrganizationAssignment::Init(aAssignedPersonAndOrganization, aRole);
}

void StepAP214_AutoDesignDateAndPersonAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndPersonItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndPersonItem>>
  StepAP214_AutoDesignDateAndPersonAssignment::Items() const
{
  return items;
}

StepAP214_AutoDesignDateAndPersonItem StepAP214_AutoDesignDateAndPersonAssignment::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignDateAndPersonAssignment::NbItems() const
{
  return items->Length();
}
