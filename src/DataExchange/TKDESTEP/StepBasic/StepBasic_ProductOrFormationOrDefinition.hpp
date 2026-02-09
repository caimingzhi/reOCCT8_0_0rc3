#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_Product;
class StepBasic_ProductDefinitionFormation;
class StepBasic_ProductDefinition;

class StepBasic_ProductOrFormationOrDefinition : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepBasic_ProductOrFormationOrDefinition();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_Product> Product() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;
};
