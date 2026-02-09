#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepAP214_ApprovalItem.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepAP214_AppliedOrganizationAssignment;
class StepBasic_Approval;
class StepAP214_AppliedSecurityClassificationAssignment;

class StepAP214_OrganizationItem : public StepAP214_ApprovalItem
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP214_OrganizationItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepAP214_AppliedOrganizationAssignment>
                  AppliedOrganizationAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_Approval> Approval() const;

  Standard_EXPORT occ::handle<StepAP214_AppliedSecurityClassificationAssignment>
                  AppliedSecurityClassificationAssignment() const;
};
