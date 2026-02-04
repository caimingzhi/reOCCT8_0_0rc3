#pragma once


#include <Standard.hpp>

#include <StepAP203_PersonOrganizationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_PersonAndOrganizationAssignment.hpp>
class StepBasic_PersonAndOrganization;
class StepBasic_PersonAndOrganizationRole;

//! Representation of STEP entity CcDesignPersonAndOrganizationAssignment
class StepAP203_CcDesignPersonAndOrganizationAssignment
    : public StepBasic_PersonAndOrganizationAssignment
{

public:
  //! Empty constructor
  Standard_EXPORT StepAP203_CcDesignPersonAndOrganizationAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_PersonAndOrganization>&
      aPersonAndOrganizationAssignment_AssignedPersonAndOrganization,
    const occ::handle<StepBasic_PersonAndOrganizationRole>& aPersonAndOrganizationAssignment_Role,
    const occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>>& aItems);

  //! Returns field Items
  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>> Items() const;

  //! Set field Items
  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_CcDesignPersonAndOrganizationAssignment,
                          StepBasic_PersonAndOrganizationAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>> theItems;
};

