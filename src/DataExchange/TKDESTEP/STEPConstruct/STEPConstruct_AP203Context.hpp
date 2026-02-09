#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepBasic_Approval;
class StepBasic_DateAndTime;
class StepBasic_PersonAndOrganization;
class StepBasic_SecurityClassificationLevel;
class StepBasic_PersonAndOrganizationRole;
class StepBasic_DateTimeRole;
class StepBasic_ApprovalRole;
class StepAP203_CcDesignPersonAndOrganizationAssignment;
class StepAP203_CcDesignSecurityClassification;
class StepAP203_CcDesignDateAndTimeAssignment;
class StepAP203_CcDesignApproval;
class StepBasic_ApprovalPersonOrganization;
class StepBasic_ApprovalDateTime;
class StepBasic_ProductCategoryRelationship;
class StepShape_ShapeDefinitionRepresentation;
class STEPConstruct_Part;
class StepRepr_NextAssemblyUsageOccurrence;

class STEPConstruct_AP203Context
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPConstruct_AP203Context();

  Standard_EXPORT occ::handle<StepBasic_Approval> DefaultApproval();

  Standard_EXPORT void SetDefaultApproval(const occ::handle<StepBasic_Approval>& app);

  Standard_EXPORT occ::handle<StepBasic_DateAndTime> DefaultDateAndTime();

  Standard_EXPORT void SetDefaultDateAndTime(const occ::handle<StepBasic_DateAndTime>& dt);

  Standard_EXPORT occ::handle<StepBasic_PersonAndOrganization> DefaultPersonAndOrganization();

  Standard_EXPORT void SetDefaultPersonAndOrganization(
    const occ::handle<StepBasic_PersonAndOrganization>& po);

  Standard_EXPORT occ::handle<StepBasic_SecurityClassificationLevel>
                  DefaultSecurityClassificationLevel();

  Standard_EXPORT void SetDefaultSecurityClassificationLevel(
    const occ::handle<StepBasic_SecurityClassificationLevel>& sc);

  Standard_EXPORT occ::handle<StepBasic_PersonAndOrganizationRole> RoleCreator() const;

  Standard_EXPORT occ::handle<StepBasic_PersonAndOrganizationRole> RoleDesignOwner() const;

  Standard_EXPORT occ::handle<StepBasic_PersonAndOrganizationRole> RoleDesignSupplier() const;

  Standard_EXPORT occ::handle<StepBasic_PersonAndOrganizationRole> RoleClassificationOfficer()
    const;

  Standard_EXPORT occ::handle<StepBasic_DateTimeRole> RoleCreationDate() const;

  Standard_EXPORT occ::handle<StepBasic_DateTimeRole> RoleClassificationDate() const;

  Standard_EXPORT occ::handle<StepBasic_ApprovalRole> RoleApprover() const;

  Standard_EXPORT void Init(const occ::handle<StepShape_ShapeDefinitionRepresentation>& sdr);

  Standard_EXPORT void Init(const STEPConstruct_Part& SDRTool);

  Standard_EXPORT void Init(const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& nauo);

  Standard_EXPORT occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> GetCreator() const;

  Standard_EXPORT occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> GetDesignOwner()
    const;

  Standard_EXPORT occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> GetDesignSupplier()
    const;

  Standard_EXPORT occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment>
                  GetClassificationOfficer() const;

  Standard_EXPORT occ::handle<StepAP203_CcDesignSecurityClassification> GetSecurity() const;

  Standard_EXPORT occ::handle<StepAP203_CcDesignDateAndTimeAssignment> GetCreationDate() const;

  Standard_EXPORT occ::handle<StepAP203_CcDesignDateAndTimeAssignment> GetClassificationDate()
    const;

  Standard_EXPORT occ::handle<StepAP203_CcDesignApproval> GetApproval() const;

  Standard_EXPORT occ::handle<StepBasic_ApprovalPersonOrganization> GetApprover() const;

  Standard_EXPORT occ::handle<StepBasic_ApprovalDateTime> GetApprovalDateTime() const;

  Standard_EXPORT occ::handle<StepBasic_ProductCategoryRelationship>
                  GetProductCategoryRelationship() const;

  Standard_EXPORT void Clear();

  Standard_EXPORT void InitRoles();

  Standard_EXPORT void InitAssembly(const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& nauo);

  Standard_EXPORT void InitSecurityRequisites();

  Standard_EXPORT void InitApprovalRequisites();

private:
  Standard_EXPORT void InitPart(const STEPConstruct_Part& SDRTool);

  occ::handle<StepBasic_Approval>                                defApproval;
  occ::handle<StepBasic_DateAndTime>                             defDateAndTime;
  occ::handle<StepBasic_PersonAndOrganization>                   defPersonAndOrganization;
  occ::handle<StepBasic_SecurityClassificationLevel>             defSecurityClassificationLevel;
  occ::handle<StepBasic_PersonAndOrganizationRole>               roleCreator;
  occ::handle<StepBasic_PersonAndOrganizationRole>               roleDesignOwner;
  occ::handle<StepBasic_PersonAndOrganizationRole>               roleDesignSupplier;
  occ::handle<StepBasic_PersonAndOrganizationRole>               roleClassificationOfficer;
  occ::handle<StepBasic_DateTimeRole>                            roleCreationDate;
  occ::handle<StepBasic_DateTimeRole>                            roleClassificationDate;
  occ::handle<StepBasic_ApprovalRole>                            roleApprover;
  occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> myCreator;
  occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> myDesignOwner;
  occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> myDesignSupplier;
  occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> myClassificationOfficer;
  occ::handle<StepAP203_CcDesignSecurityClassification>          mySecurity;
  occ::handle<StepAP203_CcDesignDateAndTimeAssignment>           myCreationDate;
  occ::handle<StepAP203_CcDesignDateAndTimeAssignment>           myClassificationDate;
  occ::handle<StepAP203_CcDesignApproval>                        myApproval;
  occ::handle<StepBasic_ApprovalPersonOrganization>              myApprover;
  occ::handle<StepBasic_ApprovalDateTime>                        myApprovalDateTime;
  occ::handle<StepBasic_ProductCategoryRelationship>             myProductCategoryRelationship;
};
