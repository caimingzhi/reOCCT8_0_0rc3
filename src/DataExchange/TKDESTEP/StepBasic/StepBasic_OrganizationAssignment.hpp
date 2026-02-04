#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Organization;
class StepBasic_OrganizationRole;

class StepBasic_OrganizationAssignment : public Standard_Transient
{

public:
  Standard_EXPORT void Init(const occ::handle<StepBasic_Organization>&     aAssignedOrganization,
                            const occ::handle<StepBasic_OrganizationRole>& aRole);

  Standard_EXPORT void SetAssignedOrganization(
    const occ::handle<StepBasic_Organization>& aAssignedOrganization);

  Standard_EXPORT occ::handle<StepBasic_Organization> AssignedOrganization() const;

  Standard_EXPORT void SetRole(const occ::handle<StepBasic_OrganizationRole>& aRole);

  Standard_EXPORT occ::handle<StepBasic_OrganizationRole> Role() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_OrganizationAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Organization>     assignedOrganization;
  occ::handle<StepBasic_OrganizationRole> role;
};

