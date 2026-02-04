#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_PersonAndOrganization;
class StepBasic_PersonAndOrganizationRole;

class StepBasic_PersonAndOrganizationAssignment : public Standard_Transient
{

public:
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_PersonAndOrganization>&     aAssignedPersonAndOrganization,
    const occ::handle<StepBasic_PersonAndOrganizationRole>& aRole);

  Standard_EXPORT void SetAssignedPersonAndOrganization(
    const occ::handle<StepBasic_PersonAndOrganization>& aAssignedPersonAndOrganization);

  Standard_EXPORT occ::handle<StepBasic_PersonAndOrganization> AssignedPersonAndOrganization()
    const;

  Standard_EXPORT void SetRole(const occ::handle<StepBasic_PersonAndOrganizationRole>& aRole);

  Standard_EXPORT occ::handle<StepBasic_PersonAndOrganizationRole> Role() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_PersonAndOrganizationAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_PersonAndOrganization>     assignedPersonAndOrganization;
  occ::handle<StepBasic_PersonAndOrganizationRole> role;
};

