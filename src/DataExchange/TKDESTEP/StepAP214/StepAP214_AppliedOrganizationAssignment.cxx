

#include <StepAP214_AppliedOrganizationAssignment.hpp>
#include <StepAP214_OrganizationItem.hpp>
#include <StepBasic_Organization.hpp>
#include <StepBasic_OrganizationRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AppliedOrganizationAssignment,
                           StepBasic_OrganizationAssignment)

StepAP214_AppliedOrganizationAssignment::StepAP214_AppliedOrganizationAssignment() = default;

void StepAP214_AppliedOrganizationAssignment::Init(
  const occ::handle<StepBasic_Organization>&                          aAssignedOrganization,
  const occ::handle<StepBasic_OrganizationRole>&                      aRole,
  const occ::handle<NCollection_HArray1<StepAP214_OrganizationItem>>& aItems)
{

  items = aItems;

  StepBasic_OrganizationAssignment::Init(aAssignedOrganization, aRole);
}

void StepAP214_AppliedOrganizationAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_OrganizationItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_OrganizationItem>>
  StepAP214_AppliedOrganizationAssignment::Items() const
{
  return items;
}

StepAP214_OrganizationItem StepAP214_AppliedOrganizationAssignment::ItemsValue(const int num) const
{
  return items->Value(num);
}

int StepAP214_AppliedOrganizationAssignment::NbItems() const
{
  return items->Length();
}
