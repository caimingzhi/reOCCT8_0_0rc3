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

//! Representation of STEP SELECT type ProductOrFormationOrDefinition
class StepBasic_ProductOrFormationOrDefinition : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepBasic_ProductOrFormationOrDefinition();

  //! Recognizes a kind of ProductOrFormationOrDefinition select type
  //! 1 -> Product from StepBasic
  //! 2 -> ProductDefinitionFormation from StepBasic
  //! 3 -> ProductDefinition from StepBasic
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as Product (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Product> Product() const;

  //! Returns Value as ProductDefinitionFormation (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;

  //! Returns Value as ProductDefinition (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;
};
