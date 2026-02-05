#pragma once

#include <Standard.hpp>

#include <StepAP214_AutoDesignGeneralOrgItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_OrganizationAssignment.hpp>
#include <Standard_Integer.hpp>
class StepBasic_Organization;
class StepBasic_OrganizationRole;
class StepAP214_AutoDesignGeneralOrgItem;

class StepAP214_AutoDesignOrganizationAssignment : public StepBasic_OrganizationAssignment
{

public:
  //! Returns a AutoDesignOrganizationAssignment
  Standard_EXPORT StepAP214_AutoDesignOrganizationAssignment();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Organization>&     aAssignedOrganization,
    const occ::handle<StepBasic_OrganizationRole>& aRole,
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>& aItems);

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>> Items()
    const;

  Standard_EXPORT StepAP214_AutoDesignGeneralOrgItem ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AutoDesignOrganizationAssignment,
                          StepBasic_OrganizationAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>> items;
};
