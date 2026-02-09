

#include <StepAP214_AutoDesignOrganizationAssignment.hpp>
#include <StepBasic_Organization.hpp>
#include <StepBasic_OrganizationRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignOrganizationAssignment,
                           StepBasic_OrganizationAssignment)

StepAP214_AutoDesignOrganizationAssignment::StepAP214_AutoDesignOrganizationAssignment() = default;

void StepAP214_AutoDesignOrganizationAssignment::Init(
  const occ::handle<StepBasic_Organization>&                                  aAssignedOrganization,
  const occ::handle<StepBasic_OrganizationRole>&                              aRole,
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>& aItems)
{

  items = aItems;

  StepBasic_OrganizationAssignment::Init(aAssignedOrganization, aRole);
}

void StepAP214_AutoDesignOrganizationAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>
  StepAP214_AutoDesignOrganizationAssignment::Items() const
{
  return items;
}

StepAP214_AutoDesignGeneralOrgItem StepAP214_AutoDesignOrganizationAssignment::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignOrganizationAssignment::NbItems() const
{
  return items->Length();
}
