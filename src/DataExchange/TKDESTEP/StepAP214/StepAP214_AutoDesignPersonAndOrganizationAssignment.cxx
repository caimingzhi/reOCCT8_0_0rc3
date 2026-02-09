

#include <StepAP214_AutoDesignPersonAndOrganizationAssignment.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepBasic_PersonAndOrganizationRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignPersonAndOrganizationAssignment,
                           StepBasic_PersonAndOrganizationAssignment)

StepAP214_AutoDesignPersonAndOrganizationAssignment::
  StepAP214_AutoDesignPersonAndOrganizationAssignment() = default;

void StepAP214_AutoDesignPersonAndOrganizationAssignment::Init(
  const occ::handle<StepBasic_PersonAndOrganization>&     aAssignedPersonAndOrganization,
  const occ::handle<StepBasic_PersonAndOrganizationRole>& aRole,
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>& aItems)
{

  items = aItems;

  StepBasic_PersonAndOrganizationAssignment::Init(aAssignedPersonAndOrganization, aRole);
}

void StepAP214_AutoDesignPersonAndOrganizationAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>
  StepAP214_AutoDesignPersonAndOrganizationAssignment::Items() const
{
  return items;
}

StepAP214_AutoDesignGeneralOrgItem StepAP214_AutoDesignPersonAndOrganizationAssignment::ItemsValue(
  const int num) const
{
  return items->Value(num);
}

int StepAP214_AutoDesignPersonAndOrganizationAssignment::NbItems() const
{
  return items->Length();
}
