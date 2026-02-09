#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinitionFormation;
class StepBasic_ProductDefinition;
class StepRepr_ConfigurationEffectivity;
class StepRepr_ConfigurationItem;
class StepBasic_SecurityClassification;
class StepAP203_ChangeRequest;
class StepAP203_Change;
class StepAP203_StartRequest;
class StepAP203_StartWork;
class StepBasic_Certification;
class StepBasic_Contract;

class StepAP203_ApprovedItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP203_ApprovedItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT occ::handle<StepRepr_ConfigurationEffectivity> ConfigurationEffectivity() const;

  Standard_EXPORT occ::handle<StepRepr_ConfigurationItem> ConfigurationItem() const;

  Standard_EXPORT occ::handle<StepBasic_SecurityClassification> SecurityClassification() const;

  Standard_EXPORT occ::handle<StepAP203_ChangeRequest> ChangeRequest() const;

  Standard_EXPORT occ::handle<StepAP203_Change> Change() const;

  Standard_EXPORT occ::handle<StepAP203_StartRequest> StartRequest() const;

  Standard_EXPORT occ::handle<StepAP203_StartWork> StartWork() const;

  Standard_EXPORT occ::handle<StepBasic_Certification> Certification() const;

  Standard_EXPORT occ::handle<StepBasic_Contract> Contract() const;
};
