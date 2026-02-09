

#include <StepAP214_AppliedPersonAndOrganizationAssignment.hpp>
#include <StepAP214_PersonAndOrganizationItem.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepBasic_PersonAndOrganizationRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AppliedPersonAndOrganizationAssignment,
                           StepBasic_PersonAndOrganizationAssignment)

StepAP214_AppliedPersonAndOrganizationAssignment::
  StepAP214_AppliedPersonAndOrganizationAssignment() = default;

void StepAP214_AppliedPersonAndOrganizationAssignment::Init(
  const occ::handle<StepBasic_PersonAndOrganization>&     aAssignedPersonAndOrganization,
  const occ::handle<StepBasic_PersonAndOrganizationRole>& aRole,
  const occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>>& aItems)
{

  items = aItems;

  StepBasic_PersonAndOrganizationAssignment::Init(aAssignedPersonAndOrganization, aRole);
}

void StepAP214_AppliedPersonAndOrganizationAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>>
  StepAP214_AppliedPersonAndOrganizationAssignment::Items() const
{
  return items;
}

StepAP214_PersonAndOrganizationItem StepAP214_AppliedPersonAndOrganizationAssignment::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AppliedPersonAndOrganizationAssignment::NbItems() const
{
  return items->Length();
}
