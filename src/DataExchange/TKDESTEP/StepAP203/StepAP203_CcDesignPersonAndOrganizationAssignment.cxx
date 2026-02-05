#include <StepAP203_CcDesignPersonAndOrganizationAssignment.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepBasic_PersonAndOrganizationRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_CcDesignPersonAndOrganizationAssignment,
                           StepBasic_PersonAndOrganizationAssignment)

//=================================================================================================

StepAP203_CcDesignPersonAndOrganizationAssignment::
  StepAP203_CcDesignPersonAndOrganizationAssignment() = default;

//=================================================================================================

void StepAP203_CcDesignPersonAndOrganizationAssignment::Init(
  const occ::handle<StepBasic_PersonAndOrganization>&
    aPersonAndOrganizationAssignment_AssignedPersonAndOrganization,
  const occ::handle<StepBasic_PersonAndOrganizationRole>& aPersonAndOrganizationAssignment_Role,
  const occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>>& aItems)
{
  StepBasic_PersonAndOrganizationAssignment::Init(
    aPersonAndOrganizationAssignment_AssignedPersonAndOrganization,
    aPersonAndOrganizationAssignment_Role);

  theItems = aItems;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>>
  StepAP203_CcDesignPersonAndOrganizationAssignment::Items() const
{
  return theItems;
}

//=================================================================================================

void StepAP203_CcDesignPersonAndOrganizationAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>>& aItems)
{
  theItems = aItems;
}
