#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinition;
class StepAP203_ChangeRequest;
class StepAP203_StartRequest;
class StepAP203_Change;
class StepAP203_StartWork;
class StepBasic_ApprovalPersonOrganization;
class StepBasic_Contract;
class StepBasic_SecurityClassification;
class StepBasic_Certification;

class StepAP203_DateTimeItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP203_DateTimeItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT occ::handle<StepAP203_ChangeRequest> ChangeRequest() const;

  Standard_EXPORT occ::handle<StepAP203_StartRequest> StartRequest() const;

  Standard_EXPORT occ::handle<StepAP203_Change> Change() const;

  Standard_EXPORT occ::handle<StepAP203_StartWork> StartWork() const;

  Standard_EXPORT occ::handle<StepBasic_ApprovalPersonOrganization> ApprovalPersonOrganization()
    const;

  Standard_EXPORT occ::handle<StepBasic_Contract> Contract() const;

  Standard_EXPORT occ::handle<StepBasic_SecurityClassification> SecurityClassification() const;

  Standard_EXPORT occ::handle<StepBasic_Certification> Certification() const;
};
