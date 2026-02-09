#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepAP214_ApprovalItem.hpp>

class StepBasic_Action;
class StepRepr_AssemblyComponentUsage;
class StepRepr_ConfigurationDesign;
class StepRepr_ConfigurationEffectivity;
class StepVisual_DraughtingModel;
class StepBasic_GeneralProperty;
class StepRepr_MakeFromUsageOption;
class StepRepr_ProductConcept;
class StepRepr_ProductDefinitionUsage;
class StepBasic_VersionedActionRequest;

class StepAP214_SecurityClassificationItem : public StepAP214_ApprovalItem
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP214_SecurityClassificationItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT virtual occ::handle<StepBasic_Action> Action() const;

  Standard_EXPORT virtual occ::handle<StepRepr_AssemblyComponentUsage> AssemblyComponentUsage()
    const;

  Standard_EXPORT virtual occ::handle<StepRepr_ConfigurationDesign> ConfigurationDesign() const;

  Standard_EXPORT virtual occ::handle<StepRepr_ConfigurationEffectivity> ConfigurationEffectivity()
    const;

  Standard_EXPORT virtual occ::handle<StepVisual_DraughtingModel> DraughtingModel() const;

  Standard_EXPORT virtual occ::handle<StepBasic_GeneralProperty> GeneralProperty() const;

  Standard_EXPORT virtual occ::handle<StepRepr_MakeFromUsageOption> MakeFromUsageOption() const;

  Standard_EXPORT virtual occ::handle<StepRepr_ProductConcept> ProductConcept() const;

  Standard_EXPORT virtual occ::handle<StepRepr_ProductDefinitionUsage> ProductDefinitionUsage()
    const;

  Standard_EXPORT virtual occ::handle<StepBasic_VersionedActionRequest> VersionedActionRequest()
    const;
};
