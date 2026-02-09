#pragma once

#include <Standard.hpp>

#include <StepAP214_PersonAndOrganizationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_PersonAndOrganizationAssignment.hpp>
#include <Standard_Integer.hpp>
class StepBasic_PersonAndOrganization;
class StepBasic_PersonAndOrganizationRole;
class StepAP214_PersonAndOrganizationItem;

class StepAP214_AppliedPersonAndOrganizationAssignment
    : public StepBasic_PersonAndOrganizationAssignment
{

public:
  Standard_EXPORT StepAP214_AppliedPersonAndOrganizationAssignment();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_PersonAndOrganization>&     aAssignedPersonAndOrganization,
    const occ::handle<StepBasic_PersonAndOrganizationRole>& aRole,
    const occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>>& aItems);

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>> Items()
    const;

  Standard_EXPORT StepAP214_PersonAndOrganizationItem ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AppliedPersonAndOrganizationAssignment,
                          StepBasic_PersonAndOrganizationAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>> items;
};
