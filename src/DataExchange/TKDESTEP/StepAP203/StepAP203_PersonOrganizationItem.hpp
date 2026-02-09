#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepAP203_Change;
class StepAP203_StartWork;
class StepAP203_ChangeRequest;
class StepAP203_StartRequest;
class StepRepr_ConfigurationItem;
class StepBasic_Product;
class StepBasic_ProductDefinitionFormation;
class StepBasic_ProductDefinition;
class StepBasic_Contract;
class StepBasic_SecurityClassification;

class StepAP203_PersonOrganizationItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP203_PersonOrganizationItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepAP203_Change> Change() const;

  Standard_EXPORT occ::handle<StepAP203_StartWork> StartWork() const;

  Standard_EXPORT occ::handle<StepAP203_ChangeRequest> ChangeRequest() const;

  Standard_EXPORT occ::handle<StepAP203_StartRequest> StartRequest() const;

  Standard_EXPORT occ::handle<StepRepr_ConfigurationItem> ConfigurationItem() const;

  Standard_EXPORT occ::handle<StepBasic_Product> Product() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT occ::handle<StepBasic_Contract> Contract() const;

  Standard_EXPORT occ::handle<StepBasic_SecurityClassification> SecurityClassification() const;
};
